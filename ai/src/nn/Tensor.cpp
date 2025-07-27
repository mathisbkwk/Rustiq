/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** Tensor implementation
*/

#include "Tensor.hpp"
#include <algorithm>
#include <numeric>
#include <random>
#include <sstream>
#include <iomanip>
#include <cmath>

namespace rustiq {

Tensor::Tensor(const std::vector<int>& shape, bool requires_grad) 
    : requires_grad(requires_grad), _shape(shape) {
    size_t total_size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<int>());
    _data.resize(total_size, 0.0f);
    this->_compute_strides();
    if (requires_grad) {
        grad = std::make_shared<Tensor>(shape, false);
    }
}

Tensor::Tensor(const std::vector<float>& data, const std::vector<int>& shape, bool requires_grad) 
    : requires_grad(requires_grad), _data(data), _shape(shape) {
    size_t expected_size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<int>());
    if (data.size() != expected_size) {
        throw std::invalid_argument("Data size doesn't match shape");
    }
    this->_compute_strides();
    if (requires_grad) {
        grad = std::make_shared<Tensor>(shape, false);
    }
}

Tensor::Tensor(const Tensor& other) 
    : requires_grad(other.requires_grad),
   _data(other._data), _shape(other._shape), _strides(other._strides) {
    if (other.grad) {
        grad = std::make_shared<Tensor>(*other.grad);
    }
}

Tensor& Tensor::operator=(const Tensor& other) {
    if (this != &other) {
        _data = other._data;
        _shape = other._shape;
        _strides = other._strides;
        requires_grad = other.requires_grad;
        if (other.grad) {
            grad = std::make_shared<Tensor>(*other.grad);
        } else {
            grad = nullptr;
        }
    }
    return *this;
}

Tensor::Tensor(Tensor&& other) noexcept 
    : grad(std::move(other.grad)), requires_grad(other.requires_grad), _data(std::move(other._data)), _shape(std::move(other._shape)),  _strides(std::move(other._strides)) {
}

Tensor& Tensor::operator=(Tensor&& other) noexcept {
    if (this != &other) {
        _data = std::move(other._data);
        _shape = std::move(other._shape);
        _strides = std::move(other._strides);
        requires_grad = other.requires_grad;
        grad = std::move(other.grad);
    }
    return *this;
}


void Tensor::_compute_strides() {
    _strides.resize(_shape.size());
    if (_shape.empty()) return;
    
    _strides.back() = 1;
    for (int i = _shape.size() - 2; i >= 0; --i) {
        _strides[i] = _strides[i + 1] * _shape[i + 1];
    }
}

size_t Tensor::_get_index(const std::vector<int>& indices) const {
    if (indices.size() != _shape.size()) {
        throw std::invalid_argument("Number of indices doesn't match tensor dimensions");
    }
    
    size_t index = 0;
    for (size_t i = 0; i < indices.size(); ++i) {
        if (indices[i] < 0 || indices[i] >= _shape[i]) {
            throw std::out_of_range("Index out of bounds");
        }
        index += indices[i] * _strides[i];
    }
    return index;
}

void Tensor::_validate_indices(const std::vector<int>& indices) const {
    if (indices.size() != _shape.size()) {
        throw std::invalid_argument("Number of indices doesn't match tensor dimensions");
    }
    for (size_t i = 0; i < indices.size(); ++i) {
        if (indices[i] < 0 || indices[i] >= _shape[i]) {
            throw std::out_of_range("Index out of bounds at dimension " + std::to_string(i));
        }
    }
}

void Tensor::_validate_shape_compatibility(const Tensor& other) const {
    if (_shape != other._shape) {
        throw std::invalid_argument("Tensor shapes are incompatible for this operation");
    }
}


Tensor Tensor::operator+(const Tensor& other) const {
    _validate_shape_compatibility(other);
    
    Tensor result(_shape, requires_grad || other.requires_grad);
    for (size_t i = 0; i < _data.size(); ++i) {
        result._data[i] = _data[i] + other._data[i];
    }
    
    if (result.requires_grad) {
        result._setup_add_backward(other);
    }
    
    return result;
}

Tensor Tensor::operator-(const Tensor& other) const {
    _validate_shape_compatibility(other);
    
    Tensor result(_shape, requires_grad || other.requires_grad);
    for (size_t i = 0; i < _data.size(); ++i) {
        result._data[i] = _data[i] - other._data[i];
    }
    
    if (result.requires_grad) {
        result._setup_sub_backward(other);
    }
    
    return result;
}

Tensor Tensor::operator*(const Tensor& other) const {
    _validate_shape_compatibility(other);
    
    Tensor result(_shape, requires_grad || other.requires_grad);
    for (size_t i = 0; i < _data.size(); ++i) {
        result._data[i] = _data[i] * other._data[i];
    }
    
    if (result.requires_grad) {
        result._setup_mul_backward(other);
    }
    
    return result;
}

Tensor Tensor::operator/(const Tensor& other) const {
    _validate_shape_compatibility(other);
    
    Tensor result(_shape, requires_grad || other.requires_grad);
    for (size_t i = 0; i < _data.size(); ++i) {
        if (std::abs(other._data[i]) < 1e-8f) {
            throw std::runtime_error("Division by zero");
        }
        result._data[i] = _data[i] / other._data[i];
    }
    
    if (result.requires_grad) {
        result._setup_div_backward(other);
    }
    
    return result;
}

Tensor Tensor::operator+(float scalar) const {
    Tensor result(_shape, requires_grad);
    for (size_t i = 0; i < _data.size(); ++i) {
        result._data[i] = _data[i] + scalar;
    }
    
    if (requires_grad) {
        auto self_ptr = std::make_shared<Tensor>(*this);
        result._parents = {self_ptr};
        result._backward_fn = [self_ptr](const Tensor& grad_output) {
            if (self_ptr->grad) {
                for (size_t i = 0; i < self_ptr->grad->_data.size(); ++i) {
                    self_ptr->grad->_data[i] += grad_output._data[i];
                }
            }
        };
    }
    
    return result;
}

Tensor Tensor::operator*(float scalar) const {
    Tensor result(_shape, requires_grad);
    for (size_t i = 0; i < _data.size(); ++i) {
        result._data[i] = _data[i] * scalar;
    }
    
    if (requires_grad) {
        auto self_ptr = std::make_shared<Tensor>(*this);
        result._parents = {self_ptr};
        result._backward_fn = [self_ptr, scalar](const Tensor& grad_output) {
            if (self_ptr->grad) {
                for (size_t i = 0; i < self_ptr->grad->_data.size(); ++i) {
                    self_ptr->grad->_data[i] += grad_output._data[i] * scalar;
                }
            }
        };
    }
    
    return result;
}


float& Tensor::operator[](const std::vector<int>& indices) {
    return _data[_get_index(indices)];
}

const float& Tensor::operator[](const std::vector<int>& indices) const {
    return _data[_get_index(indices)];
}

float& Tensor::at(const std::vector<int>& indices) {
    _validate_indices(indices);
    return _data[_get_index(indices)];
}

const float& Tensor::at(const std::vector<int>& indices) const {
    _validate_indices(indices);
    return _data[_get_index(indices)];
}


void Tensor::reshape(const std::vector<int>& new_shape) {
    size_t new_size = std::accumulate(new_shape.begin(), new_shape.end(), 1, std::multiplies<int>());
    if (new_size != _data.size()) {
        throw std::invalid_argument("New shape is incompatible with current data size");
    }
    _shape = new_shape;
    _compute_strides();
}

Tensor Tensor::transpose() const {
    if (_shape.size() != 2) {
        throw std::invalid_argument("transpose() only supports 2D tensors");
    }
    
    std::vector<int> new_shape = {_shape[1], _shape[0]};
    Tensor result(new_shape, requires_grad);
    
    for (int i = 0; i < _shape[0]; ++i) {
        for (int j = 0; j < _shape[1]; ++j) {
            result[{j, i}] = (*this)[{i, j}];
        }
    }
    
    return result;
}

std::vector<int> Tensor::get_shape() const {
    return _shape;
}

size_t Tensor::size() const {
    return _data.size();
}

int Tensor::ndim() const {
    return _shape.size();
}


void Tensor::backward(const Tensor& grad_input) {
    if (!requires_grad) return;
    
    if (grad_input._data.empty()) {
        if (!grad) {
            grad = std::make_shared<Tensor>(_shape, false);
        }
        std::fill(grad->_data.begin(), grad->_data.end(), 1.0f);
    } else {
        if (!grad) {
            grad = std::make_shared<Tensor>(grad_input);
        } else {
            for (size_t i = 0; i < grad->_data.size(); ++i) {
                grad->_data[i] += grad_input._data[i];
            }
        }
    }
    
    if (_backward_fn) {
        _backward_fn(grad_input._data.empty() ? *grad : grad_input);
    }
}

void Tensor::zero_grad() {
    if (grad) {
        std::fill(grad->_data.begin(), grad->_data.end(), 0.0f);
    }
}

void Tensor::set_requires_grad(bool requires_grad_val) {
    requires_grad = requires_grad_val;
    if (requires_grad && !grad) {
        grad = std::make_shared<Tensor>(_shape, false);
    }
}

bool Tensor::get_requires_grad() const {
    return requires_grad;
}


void Tensor::fill(float value) {
    std::fill(_data.begin(), _data.end(), value);
}

void Tensor::zero() {
    fill(0.0f);
}

void Tensor::ones() {
    fill(1.0f);
}

void Tensor::random_normal(float mean, float std) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<float> dist(mean, std);
    
    for (float& val : _data) {
        val = dist(gen);
    }
}

void Tensor::random_uniform(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    
    for (float& val : _data) {
        val = dist(gen);
    }
}


float Tensor::sum() const {
    return std::accumulate(_data.begin(), _data.end(), 0.0f);
}

float Tensor::mean() const {
    return sum() / _data.size();
}

float Tensor::max() const {
    return *std::max_element(_data.begin(), _data.end());
}

float Tensor::min() const {
    return *std::min_element(_data.begin(), _data.end());
}


const std::vector<float>& Tensor::data() const {
    return _data;
}

std::vector<float>& Tensor::data() {
    return _data;
}


void Tensor::print() const {
    std::cout << to_string() << std::endl;
}

std::string Tensor::to_string() const {
    std::stringstream ss;
    ss << "Tensor(shape=[";
    for (size_t i = 0; i < _shape.size(); ++i) {
        ss << _shape[i];
        if (i < _shape.size() - 1) ss << ", ";
    }
    ss << "], requires_grad=" << (requires_grad ? "true" : "false") << ")\n";
    
    if (_shape.size() == 1) {
        ss << "[";
        for (size_t i = 0; i < _data.size(); ++i) {
            ss << std::fixed << std::setprecision(4) << _data[i];
            if (i < _data.size() - 1) ss << ", ";
        }
        ss << "]";
    } else if (_shape.size() == 2) {
        ss << "[";
        for (int i = 0; i < _shape[0]; ++i) {
            ss << "[";
            for (int j = 0; j < _shape[1]; ++j) {
                ss << std::fixed << std::setprecision(4) << (*this)[{i, j}];
                if (j < _shape[1] - 1) ss << ", ";
            }
            ss << "]";
            if (i < _shape[0] - 1) ss << ",\n ";
        }
        ss << "]";
    } else {
        ss << "[... tensor with " << _data.size() << " elements ...]";
    }
    
    return ss.str();
}

Tensor Tensor::zeros(const std::vector<int>& shape, bool requires_grad) {
    Tensor result(shape, requires_grad);
    result.zero();
    return result;
}

Tensor Tensor::ones(const std::vector<int>& shape, bool requires_grad) {
    Tensor result(shape, requires_grad);
    result.ones();
    return result;
}

Tensor Tensor::eye(int n, bool requires_grad) {
    Tensor result({n, n}, requires_grad);
    for (int i = 0; i < n; ++i) {
        result[{i, i}] = 1.0f;
    }
    return result;
}

Tensor Tensor::randn(const std::vector<int>& shape, bool requires_grad) {
    Tensor result(shape, requires_grad);
    result.random_normal();
    return result;
}

Tensor Tensor::rand(const std::vector<int>& shape, bool requires_grad) {
    Tensor result(shape, requires_grad);
    result.random_uniform();
    return result;
}


void Tensor::_setup_add_backward(const Tensor& other) {
    auto self_ptr = std::make_shared<Tensor>(*this);
    auto other_ptr = std::make_shared<Tensor>(other);
    
    _parents = {self_ptr, other_ptr};
    _backward_fn = [self_ptr, other_ptr](const Tensor& grad_output) {
        if (self_ptr->requires_grad && self_ptr->grad) {
            for (size_t i = 0; i < self_ptr->grad->_data.size(); ++i) {
                self_ptr->grad->_data[i] += grad_output._data[i];
            }
        }
        if (other_ptr->requires_grad && other_ptr->grad) {
            for (size_t i = 0; i < other_ptr->grad->_data.size(); ++i) {
                other_ptr->grad->_data[i] += grad_output._data[i];
            }
        }
    };
}

void Tensor::_setup_mul_backward(const Tensor& other) {
    auto self_ptr = std::make_shared<Tensor>(*this);
    auto other_ptr = std::make_shared<Tensor>(other);
    
    _parents = {self_ptr, other_ptr};
    _backward_fn = [self_ptr, other_ptr](const Tensor& grad_output) {
        if (self_ptr->requires_grad && self_ptr->grad) {
            for (size_t i = 0; i < self_ptr->grad->_data.size(); ++i) {
                self_ptr->grad->_data[i] += grad_output._data[i] * other_ptr->_data[i];
            }
        }
        if (other_ptr->requires_grad && other_ptr->grad) {
            for (size_t i = 0; i < other_ptr->grad->_data.size(); ++i) {
                other_ptr->grad->_data[i] += grad_output._data[i] * self_ptr->_data[i];
            }
        }
    };
}

Tensor operator+(float scalar, const Tensor& tensor) {
    return tensor + scalar;
}

Tensor operator*(float scalar, const Tensor& tensor) {
    return tensor * scalar;
}

std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {
    os << tensor.to_string();
    return os;
}

}