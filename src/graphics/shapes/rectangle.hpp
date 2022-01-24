#pragma once

#include "./model2D.hpp"

namespace graphics
{
    namespace shapes
    {
        class Rectangle : public Model2D
        {
        public:
            Rectangle();
            Rectangle(const math::Vector &origin, double width, double height);
            Rectangle(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color);
            Rectangle(const Rectangle &other);
            Rectangle(const Rectangle &&other);
            ~Rectangle();

            Rectangle &operator=(const Rectangle &other);
            Rectangle &operator=(const Rectangle &&other);

        private:
            double width;
            double height;

            void buildPoints(const math::Vector &origin, double width, double height);
        };
    }
}