//
// Created by fangl on 2023/8/31.
//

#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QVector2D>
#include <utility>


class Point
{
public:
    // 颜色和size留到后面来实现
    Point(const QVector2D& position, QColor color, float size)
        : id(nextID++) ,m_position(position), m_color(std::move(color)), m_size(size) { }

    explicit Point(const QVector2D& position)
        : id(nextID++), m_position(position)
    {
        m_color = Qt::white;
        m_size = 0.1f;
    }

    int getID() const;

    static void resetID() {
        nextID = 0;
    }

    // getter and setter for position
    QVector2D getPosition() const;
    void setPosition(const QVector2D& position);

    // getter and setter for color
    QColor getColor() const;
    void setColor(const QColor& color);

    // getter and setter for size
    float getSize() const;
    void setSize(float size);

    bool operator==(const Point& other) const;

private:
    int id;
    static inline int nextID = 0;

    QVector2D m_position;
    QColor m_color = Qt::white;
    float m_size;   // display size
};

// 管理所有Point，以及相应的数据
class Points
{
public:
    void clearData();

    const QVector<Point>& getPoints() const;
    const QVector<QVector2D>& getPointsData() const;
    const QVector<QColor>& getPointsColorData() const;
    int getPointsSize();

    void addPoint(const Point& point);
    void addPoint(QVector2D pos);

    bool removePoint(const Point& point);
    bool removePoint(int id);

    void setPointColor(int index, QColor pointColor);

private:
    // 这两个数据一定要同步！
    QVector<Point> m_points;
    QVector<QVector2D> m_pointsData;
    QVector<QColor> m_colorsData;
};

#endif //POINT_H
