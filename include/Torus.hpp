#pragma once
#ifndef TORUS_HPP
#define TORUS_HPP

namespace cpp
{
    template<typename T, uint32_t TDim1, uint32_t ... TDims>
    class Torus
    {
    public:
        static constexpr size_t N = (sizeof ... (TDims)) + 1;

        Torus()
        {
            std::initializer_list init{ TDim1, TDims... };

            std::copy(init.begin(), init.end(), this->dimensions.begin());
            auto size = std::reduce(this->dimensions.begin(), this->dimensions.end(), 1, std::multiplies<uint32_t>());
            data.resize(size);

            this->CalculateAccumulatedDimensions();
        }

        size_t size() { return this->data.size(); }

        T& item(const std::array<size_t, N>& addr) { return this->data[this->ResolveAddress(addr)]; }

        const T& item(const std::array<size_t, N>& addr) const { return this->data[this->ResolveAddress(addr)]; }

    private:
        std::array<size_t, N> dimensions;
        std::array<size_t, N> accumulatedDims;
        std::vector<T> data;

        size_t ResolveAddress(const std::array<size_t, N>& addr) const
        {
            size_t res = addr[N - 1];

            for (int i = 0; i < N - 1; i++)
            {
                res += addr[i - 1] * this->dimensions[i];
            }
        }
    };
} // namespace cpp

#endif /* TORUS_HPP */