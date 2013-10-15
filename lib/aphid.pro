TEMPLATE = lib
CONFIG += staticlib thread release
CONFIG   -= qt
PARENTPROJ = ..
SHAREDDIR = ../shared
INCLUDEPATH = $${SHAREDDIR}

INCLUDEPATH += ../mallard ../shared ../lapl ../catmullclark ../easymodel ../../ofl/opium ../fit

HEADERS = ../shared/AllMath.h \
                ../shared/Vector3F.h \
                ../shared/Vector2F.h \
                ../shared/Matrix44F.h \
                ../shared/Matrix33F.h \
                ../shared/Ray.h \
                ../shared/RayIntersectionContext.h \
                ../shared/IntersectionContext.h \
                ../shared/BaseCamera.h \
                ../shared/PerspectiveCamera.h \
                ../shared/BaseDrawer.h \
                ../shared/KdTreeDrawer.h \
                ../shared/SpaceHandle.h \
                ../shared/TypedEntity.h \
                ../shared/Geometry.h \
                ../shared/BaseMesh.h \
                ../shared/TriangleMesh.h \
                ../shared/GeoElement.h \
                ../shared/Vertex.h \
                ../shared/Edge.h \
                ../shared/Facet.h \
                ../shared/BaseField.h \
                ../shared/BaseDeformer.h \
                ../shared/KdTreeNode.h \
                ../shared/Primitive.h \
                ../shared/PrimitiveFilter.h \
                ../shared/BuildKdTreeContext.h \
                ../shared/KdTreeNodeArray.h \
                ../shared/KdTree.h \
                ../shared/PrimitiveArray.h \
                ../shared/IndexArray.h \
                ../shared/BaseArray.h \
                ../shared/ClassificationStorage.h \
                ../shared/KdTreeBuilder.h \
                ../shared/SplitEvent.h \
                ../shared/MinMaxBins.h \
                ../shared/BuildKdTreeStream.h \
                ../shared/IndexList.h \
                ../shared/BoundingBoxList.h \
                ../shared/SelectionArray.h \
                ../shared/ComponentConversion.h \
                ../shared/BarycentricCoordinate.h \
                ../shared/EasemodelUtil.h \
                ../shared/GeodesicSphereMesh.h \
                                ../shared/PyramidMesh.h \
                                ../shared/CubeMesh.h \
                ../shared/AnchorGroup.h \
                ../shared/BaseCurve.h \
                ../shared/VertexPath.h \
                ../shared/MeshTopology.h \
                ../shared/PatchMesh.h \
                                ../shared/BezierCurve.h \
                                ../shared/ToolContext.h \
                                ../shared/BiLinearInterpolate.h \
                                ../shared/LinearInterpolate.h \
                ../shared/Plane.h \
                ../shared/PointInsidePolygonTest.h \
                                ../shared/AccPatchMesh.h \
                                ../shared/CircleCurve.h \
                                ../shared/InverseBilinearInterpolate.h \
                                ../shared/Segment.h \
                                ../shared/Patch.h \
                                ../shared/BaseBrush.h \
                                ../shared/QuickSort.h \
                                ../shared/GLight.h \
                                ../shared/GMaterial.h \
                                ../shared/GProfile.h \
                                ../shared/BaseTessellator.h \
                                ../shared/CollisionRegion.h \
                                ../shared/DrawBuffer.h \
                                ../shared/BlockDrawBuffer.h \
                ../shared/BaseScene.h \
    ../shared/BoundingBox.h \
    ../shared/BoundingRectangle.h \
    ../shared/AllHdf.h \
    ../shared/HObject.h \
    ../shared/HDocument.h \
    ../shared/HGroup.h \
    ../shared/HDataset.h \
    ../shared/HAttribute.h \
    ../shared/VerticesHDataset.h \
    ../shared/IndicesHDataset.h \
    ../shared/FloatsHDataset.h \
    ../shared/HIntAttribute.h \
    ../shared/HFloatAttribute.h \
    ../shared/HStringAttribute.h \
    ../shared/HCharData.h \
    ../shared/HBase.h \
    ../shared/HWorld.h \
    ../shared/HMesh.h \
    ../shared/BaseImage.cpp \
    ../shared/zEXRImage.h \
    ../shared/BaseFile.h \
    ../shared/BakeDeformer.h \
    ../shared/PlaybackControl.h \
    ../shared/CacheFile.h \
    ../shared/BaseState.h \
    ../shared/HFile.h \
    ../shared/HRFile.h \
                                ../lapl/VertexAdjacency.h \
                ../lapl/Anchor.h \
                ../catmullclark/BaseQuad.h \
                ../catmullclark/LODQuad.h \
                ../catmullclark/accPatch.h \
                ../catmullclark/accStencil.h \
                ../catmullclark/bezierPatch.h \
                ../catmullclark/tessellator.h \
                ../catmullclark/AccCorner.h \
                ../catmullclark/AccEdge.h \
                ../catmullclark/AccInterior.h \
                ../catmullclark/BezierDrawer.h
SOURCES = ../shared/Vector3F.cpp \
                ../shared/Vector2F.cpp \
                ../shared/Matrix44F.cpp \
                ../shared/Matrix33F.cpp \
                ../shared/Ray.cpp \
                ../shared/RayIntersectionContext.cpp \
                ../shared/IntersectionContext.cpp \
                ../shared/BaseCamera.cpp \
                ../shared/PerspectiveCamera.cpp \
                ../shared/BaseDrawer.cpp \
                ../shared/KdTreeDrawer.cpp \
                ../shared/SpaceHandle.cpp \
                ../shared/TypedEntity.cpp \
                ../shared/Geometry.cpp \
                ../shared/BaseMesh.cpp \
                ../shared/TriangleMesh.cpp \
                ../shared/GeoElement.cpp \
                ../shared/Vertex.cpp \
                ../shared/Edge.cpp \
                ../shared/Facet.cpp \
                ../shared/BaseField.cpp \
                ../shared/BaseDeformer.cpp \
                ../shared/KdTreeNode.cpp \
                ../shared/Primitive.cpp \
                ../shared/PrimitiveFilter.cpp \
                ../shared/BuildKdTreeContext.cpp \
                ../shared/KdTreeNodeArray.cpp \
                ../shared/KdTree.cpp \
                ../shared/PrimitiveArray.cpp \
                ../shared/IndexArray.cpp \
                ../shared/BaseArray.cpp \
                ../shared/ClassificationStorage.cpp \
                ../shared/KdTreeBuilder.cpp \
                ../shared/SplitEvent.cpp \
                ../shared/MinMaxBins.cpp \
                ../shared/BuildKdTreeStream.cpp \
                ../shared/IndexList.cpp \
                ../shared/BoundingBoxList.cpp \
                ../shared/SelectionArray.cpp \
                ../shared/ComponentConversion.cpp \
                ../shared/BarycentricCoordinate.cpp \
                ../shared/EasemodelUtil.cpp \
                ../shared/GeodesicSphereMesh.cpp \
                ../shared/PyramidMesh.cpp \
                ../shared/CubeMesh.cpp \
                ../shared/AnchorGroup.cpp \
                ../shared/BaseCurve.cpp \
                ../shared/VertexPath.cpp \
                ../shared/MeshTopology.cpp \
                ../shared/PatchMesh.cpp \
                                ../shared/BezierCurve.cpp \
                                ../shared/ToolContext.cpp \
                                ../shared/BiLinearInterpolate.cpp \
                                ../shared/LinearInterpolate.cpp \
                ../shared/Plane.cpp \
                ../shared/PointInsidePolygonTest.cpp \
                                ../shared/AccPatchMesh.cpp \
                                ../shared/CircleCurve.cpp \
                                ../shared/InverseBilinearInterpolate.cpp \
                                ../shared/Segment.cpp \
                                ../shared/Patch.cpp \
                                ../shared/BaseBrush.cpp \
                                ../shared/QuickSort.cpp \
                                ../shared/GLight.cpp \
                                ../shared/GMaterial.cpp \
                                ../shared/GProfile.cpp \
                                ../shared/BaseTessellator.cpp \
                                ../shared/CollisionRegion.cpp \
                                ../shared/DrawBuffer.cpp \
                                ../shared/BlockDrawBuffer.cpp \
                ../shared/BaseScene.cpp \
    ../shared/BoundingBox.cpp \
    ../shared/BoundingRectangle.cpp \
    ../shared/HObject.cpp \
    ../shared/HDocument.cpp \
    ../shared/HGroup.cpp \
    ../shared/HDataset.cpp \
    ../shared/HAttribute.cpp \
    ../shared/VerticesHDataset.cpp \
    ../shared/IndicesHDataset.cpp \
        ../shared/FloatsHDataset.cpp \
    ../shared/HIntAttribute.cpp \
    ../shared/HFloatAttribute.cpp \
    ../shared/HStringAttribute.cpp \
    ../shared/HCharData.cpp \
    ../shared/HBase.cpp \
    ../shared/HWorld.cpp \
    ../shared/HMesh.cpp \
    ../shared/BaseImage.cpp \
    ../shared/zEXRImage.cpp \
        ../shared/BaseFile.cpp \
    ../shared/BakeDeformer.cpp \
    ../shared/PlaybackControl.cpp \
    ../shared/CacheFile.cpp \
    ../shared/BaseState.cpp \
    ../shared/HFile.cpp \
    ../shared/HRFile.cpp \
                                ../lapl/VertexAdjacency.cpp \
                ../lapl/Anchor.cpp \
                ../catmullclark/BaseQuad.cpp \
                ../catmullclark/LODQuad.cpp \
                ../catmullclark/accPatch.cpp \
                ../catmullclark/accStencil.cpp \
                ../catmullclark/bezierPatch.cpp \
                ../catmullclark/tessellator.cpp \
                ../catmullclark/AccCorner.cpp \
                ../catmullclark/AccEdge.cpp \
                ../catmullclark/AccInterior.cpp \
                ../catmullclark/BezierDrawer.cpp

TARGET  = aphid
macx {
    INCLUDEPATH += ../../Library/boost_1_44_0 \
                    ../../Library/hdf5/include \
                    /usr/local/include/OpenEXR
}
win32 {
    HEADERS += ../shared/gExtension.h
    SOURCES += ../shared/gExtension.cpp
    INCLUDEPATH += D:/usr/local/include D:/ofl/shared \
                   D:/usr/hdf5/include \
                   D:/usr/libxml2x64/include D:/usr/eigen3
}
