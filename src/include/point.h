//
// Created by fangl on 2023/8/31.
//

#ifndef POINT_H
#define POINT_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>

#include <utility>


class Point
{
public:
    // 颜色和size留到后面来实现
    Point(const QVector2D& position, QVector3D color, float size)
        : id(nextID++) ,m_position(position), m_color(color), m_size(size) { }

    explicit Point(const QVector2D& position)
        : id(nextID++), m_position(position)
    {
        m_color = {1.0f, 1.0f, 1.0f};
        m_size = 1.0f;
    }

    int getID() const;

    static void resetID() {
        nextID = 0;
    }

    // getter and setter for position
    QVector2D getPosition() const;
    void setPosition(const QVector2D& position);

    // getter and setter for color
    QVector3D getColor() const;
    void setColor(const QVector3D& color);

    // getter and setter for size
    float getSize() const;
    void setSize(float size);

    bool operator==(const Point& other) const;

private:
    int id;
    static inline int nextID = 0;

    QVector2D m_position;
    QVector3D m_color = {1.0f, 1.0f, 1.0f};
    float m_size;   // display size
};

// 管理所有Point，以及相应的数据
class Points
{
public:
    void clearData();

    const QVector<Point>& getPoints() const;
    const QVector<QVector2D>& getPointsData() const;
    const QVector<QVector3D>& getPointsColorData() const;
    int getPointsSize();

    void addPoint(const Point& point);
    void addPoint(QVector2D pos);

    bool removePoint(const Point& point);
    bool removePoint(int id);

    void setPointPosition(int index, QVector2D position);
    void movePointDeltaPosition(int index, QVector2D deltaPos);
    QVector2D getIndexPosition(int index);

    void setPointColor(int index, QVector3D pointColor);

private:
    // 这两个数据一定要同步！
    QVector<Point> m_points;
    QVector<QVector2D> m_pointsData;
    QVector<QVector3D> m_colorsData;
};

#endif //POINT_H
