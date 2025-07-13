/*
** EPITECH PROJECT, 2025
** rustiq_ai
** File description:
** 07
*/

#ifndef TENSOR_HPP
#define TENSOR_HPP



#include <functional>
#include <memory>
#include <vector>


namespace rustiq {
    class Tensor {
        public:
            Tensor(const std::vector<int>& shape);
            Tensor(const std::vector<float>& data, const std::vector<int>& shape);
            Tensor() = default;
            
            ~Tensor();
    
            Tensor operator+(const Tensor& other) const;
            Tensor operator-(const Tensor& other) const;
            Tensor operator*(const Tensor& other) const;
            
            float& operator[](const std::vector<int>& indices);
            const float& operator[](const std::vector<int>& indices) const;
            
            void reshape(const std::vector<int>& new_shape);
            Tensor transpose();
            std::vector<int> get_shape() const;
            size_t size() const;
            void backward(const Tensor& grad);
            
            std::shared_ptr<Tensor> grad;
            bool _requires_grad;
        private:
            std::vector<float> _data;
            std::vector<int> _shape;
            std::vector<int> _strides;
            std::function<void(const Tensor &)> _backward;
            std::vector<std::shared_ptr<Tensor>> _parents;
    };
}



#endif //TENSOR_HPP
