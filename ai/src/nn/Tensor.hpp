/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** Tensor class for neural network computations
*/
#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <functional>
#include <memory>
#include <vector>
#include <iostream>

namespace rustiq {
    class Tensor {
        public:
            Tensor(const std::vector<int>& shape, bool requires_grad = false);
            Tensor(const std::vector<float>& data, const std::vector<int>& shape, bool requires_grad = false);
            Tensor() = default;
            
            Tensor(const Tensor& other);
            Tensor& operator=(const Tensor& other);
            
            Tensor(Tensor&& other) noexcept;
            Tensor& operator=(Tensor&& other) noexcept;
            
            ~Tensor() = default;
    
            Tensor operator+(const Tensor& other) const;
            Tensor operator-(const Tensor& other) const;
            Tensor operator*(const Tensor& other) const;
            Tensor operator/(const Tensor& other) const;
            
            Tensor operator+(float scalar) const;
            Tensor operator-(float scalar) const;
            Tensor operator*(float scalar) const;
            Tensor operator/(float scalar) const;
            
            float& operator[](const std::vector<int>& indices);
            const float& operator[](const std::vector<int>& indices) const;
            float& at(const std::vector<int>& indices);
            const float& at(const std::vector<int>& indices) const;
            
            void reshape(const std::vector<int>& new_shape);
            Tensor transpose() const;
            Tensor transpose(const std::vector<int>& axes) const;
            std::vector<int> get_shape() const;
            size_t size() const;
            int ndim() const;
            
            void backward(const Tensor& grad = Tensor());
            void zero_grad();
            void set_requires_grad(bool requires_grad);
            bool get_requires_grad() const;
            
            void fill(float value);
            void zero();
            void ones();
            void random_normal(float mean = 0.0f, float std = 1.0f);
            void random_uniform(float min = 0.0f, float max = 1.0f);
            
            float sum() const;
            float mean() const;
            float max() const;
            float min() const;
            
            const std::vector<float>& data() const;
            std::vector<float>& data();
            
            void print() const;
            std::string to_string() const;
            
            static Tensor zeros(const std::vector<int>& shape, bool requires_grad = false);
            static Tensor ones(const std::vector<int>& shape, bool requires_grad = false);
            static Tensor eye(int n, bool requires_grad = false);
            static Tensor randn(const std::vector<int>& shape, bool requires_grad = false);
            static Tensor rand(const std::vector<int>& shape, bool requires_grad = false);
        public:
            std::shared_ptr<Tensor> grad;
            bool requires_grad;
            
        private:
            std::vector<float> _data;
            std::vector<int> _shape;
            std::vector<int> _strides;
            std::function<void(const Tensor&)> _backward_fn;
            std::vector<std::shared_ptr<Tensor>> _parents;
            
            void _compute_strides();
            size_t _get_index(const std::vector<int>& indices) const;
            void _validate_indices(const std::vector<int>& indices) const;
            void _validate_shape_compatibility(const Tensor& other) const;
            void _broadcast_check(const Tensor& other) const;
            
            void _setup_add_backward(const Tensor& other);
            void _setup_sub_backward(const Tensor& other);
            void _setup_mul_backward(const Tensor& other);
            void _setup_div_backward(const Tensor& other);
    };
    
    Tensor operator+(float scalar, const Tensor& tensor);
    Tensor operator-(float scalar, const Tensor& tensor);
    Tensor operator*(float scalar, const Tensor& tensor);
    Tensor operator/(float scalar, const Tensor& tensor);
    
    std::ostream& operator<<(std::ostream& os, const Tensor& tensor);
}

#endif // TENSOR_HPP