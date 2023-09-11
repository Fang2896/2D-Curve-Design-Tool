//
// Created by fangl on 2023/9/10.
//

#include "point.h"
#include <QDebug>


int Point::getID() const {
    return id;
}

// getter and setter for position
QVector2D Point::getPosition() const { return m_position; }
void Point::setPosition(const QVector2D& position) { m_position = position; }

// getter and setter for color
QVector3D Point::getColor() const { return m_color; }
void Point::setColor(const QVector3D& color) { m_color = color; }

// getter and setter for size
float Point::getSize() const { return m_size; }
void Point::setSize(float size) { m_size = size; }

bool Point::operator==(const Point& other) const {
    return id == other.id;
}


void Points::clearData() {
    m_points.clear();
    m_pointsData.clear();

    Point::resetID();
}


// 注意这两个函数的两个const
const QVector<Point>& Points::getPoints() const {
    return m_points;
}

const QVector<QVector2D>& Points::getPointsData() const {
    return m_pointsData;
}

const QVector<QVector3D>& Points::getPointsColorData() const {
    return m_colorsData;
}

int Points::getPointsSize() {
    return m_points.size();
}

void Points::addPoint(const Point& point) {
    m_points.append(point);
    m_pointsData.append(point.getPosition());
    m_colorsData.append(point.getColor());
}

void Points::addPoint(QVector2D pos) {
    auto newPoint = Point(pos);
    qDebug() << "Add New Point, position: [" <<  pos << "], id : " << newPoint.getID();
    m_points.append(newPoint);
    m_pointsData.append(pos);
    m_colorsData.append({1.0f, 1.0f, 1.0f});
}


bool Points::removePoint(const Point& point) {
    auto it = std::find(m_points.begin(), m_points.end(), point);
    if(it != m_points.end()) {
        int index = std::distance(m_points.begin(), it);
        m_points.erase(it);
        m_pointsData.erase(m_pointsData.begin() + index);
        m_colorsData.erase(m_colorsData.begin() + index);
        return true;
    }

    return false;
}

bool Points::removePoint(int id) {
    for(auto it = m_points.begin(); it != m_points.end(); it++) {
        if(it->getID() == id) {
            int index = std::distance(m_points.begin(), it);
            m_points.erase(it);
            m_pointsData.erase(m_pointsData.begin() + index);
            m_colorsData.erase(m_colorsData.begin() + index);
            return true;
        }
    }

    return false;
}

void Points::setPointPosition(int index, QVector2D position) {
    m_points[index].setPosition(position);
    m_pointsData[index] = position;
}


void Points::setPointColor(int index, QVector3D pointColor) {
    m_points[index].setColor(pointColor);
    m_colorsData[index] = pointColor;
}


