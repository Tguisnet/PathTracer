#pragma once

#include <OpenMesh/Core/Mesh/PolyConnectivity.hh>
#include <raytracer/types/triangle.hh>

namespace raytracer
{
    struct Object;

    class FacesRange
    {
        /*
         * Not a conforming iterator for now: cannot be applied to most STL
         * algorithms. Diffucult to change due to the Triangle creation.
         */
        class FacesIterator
        {
            using FaceHandle = OpenMesh::FaceHandle;
            using VertexHandle = OpenMesh::VertexHandle;
            using ConstFaceIter = OpenMesh::PolyConnectivity::ConstFaceIter;

        public:
            FacesIterator(const Object& object, ConstFaceIter iter)
                    : object_{object}
                    , iter_{iter}
            {}

            FacesIterator& operator++()
            {
                ++iter_;
                return *this;
            }

            FacesIterator operator++(int)
            {
                auto copy = *this;
                ++(*this);
                return copy;
            }

            bool operator==(const FacesIterator& other) const
            {
                return iter_ == other.iter_;
            }

            bool operator!=(const FacesIterator& other) const
            {
                return !(*this == other);
            }

            Triangle operator*() const;

        private:
            const Object& object_;
            ConstFaceIter iter_;
        };

    public:
        FacesRange(const Object& mesh)
                : object_{mesh}
        {}

        FacesIterator begin() const;

        FacesIterator end() const;

    private:
        const Object& object_;
    };
}
