#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "scene/SceneObject.h"

/**
 * @brief Box/Cube primitive object
 *
 * Represents a rectangular prism with configurable width, height, and depth.
 * Default dimensions: 1m × 1m × 1m cube.
 * Geometry: 8 vertices, 12 edges, 6 faces.
 */
class BoxObject : public SceneObject
{
    Q_OBJECT

public:
    explicit BoxObject(Qt3DCore::QNode *parent = nullptr);
    BoxObject(float width, float height, float depth, Qt3DCore::QNode *parent = nullptr);
    ~BoxObject() override;

    // Override to handle width/height/depth separately
    void setDimensions(const QVector3D& dim) override;
    void setDimensions(float width, float height, float depth);

    float width() const { return dimensions().x(); }
    float height() const { return dimensions().y(); }
    float depth() const { return dimensions().z(); }

protected:
    void generateMesh() override;

private:
    void initialize();
};

#endif // BOXOBJECT_H
