#pragma once

#include "./../../math/matrix.hpp"
#include "./../color/rgb.hpp"

namespace graphics
{
    namespace shapes
    {
        class Model
        {
        public:
            Model();
            Model(const math::Matrix &matrix);
            Model(const math::Matrix &matrix, const graphics::color::RGBA &color);
            Model(const Model &other);
            Model(const Model &&other);
            virtual ~Model() = default;

            Model &operator=(const Model &other);
            Model &operator=(const Model &&other);

            virtual void translate(const math::Vector &vector) = 0;
            virtual void scale(const math::Vector &center, const math::Vector &vector) = 0;
            virtual void rotate(const math::Vector &center, double radians) = 0;
            virtual void transform(const math::Matrix &matrix) = 0;
            virtual void transform(const math::Vector &center, const math::Vector &scale, double radians) = 0;

            virtual void draw() = 0;

        protected:
            math::Matrix points;
            color::RGBA color;
        };
    }
}