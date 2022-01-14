#include "Object.h"
#include "Game.h"

Object::Object() : QGraphicsPixmapItem(0)
{
	collidable = true;
	walkable   = false;

	// game mechanics are based on bounding rects only
	// this simplifies (a lot) collision detections, but could
	// be a limit if we have to implement tilted elements
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

	// add to scene
	Game::instance()->getScene()->addItem(this);
}

Direction Object::touchingDirection(Object* item)
{
    // get scene bounding rects
    QRectF curr_rect =  sceneBoundingRect();
    QRectF item_rect =  item->sceneBoundingRect();

    // calculate intersection rectangle (IR)
    int xi0 = std::max(curr_rect.x(), item_rect.x());
    int yi0 = std::max(curr_rect.y(), item_rect.y());
    int xi1 = std::min(curr_rect.x() + curr_rect.width(), item_rect.x() + item_rect.width());
    int yi1 = std::min(curr_rect.y() + curr_rect.height(), item_rect.y() + item_rect.height());

    // IR is null along horizontal axis an non-null along vertical
    // --> horizontal touch
    if(xi0 == xi1 && yi1 > yi0)
    {
        // horizontal touch coordinate coincides with left side of current rectangle
        if(xi0 == curr_rect.x())
            return LEFT;
        else
            return RIGHT;
    }
    // IR is null along vertical axis an non-null along horizontal
    // --> vertical touch
    else if(yi0 == yi1 && xi1 > xi0)
    {
         // vertical touch coordinate coincides with top side of current rectangle
        if(yi0 == curr_rect.y())
            return UP;
        else
            return DOWN;
    }

    return UNKNOWN;
}

Direction Object::collisionDirection(Object* item)
{
    // get scene bounding rects
    QRectF curr_rect =  sceneBoundingRect();
    QRectF item_rect =  item->sceneBoundingRect();

    // w/o intersection, we cannot detect collision direction
    if(!curr_rect.intersects(item_rect))
        return UNKNOWN;

    // calculate intersection rectangle (IR)
    QRectF interRect = curr_rect.intersected(item_rect);

    // IR is vertical
    // --> collision is horizontal
    if(interRect.width() < interRect.height())
    {
        // left side of IR coincides with left side of current rectangle
        if(interRect.left() == curr_rect.x())
            return LEFT;
        else
            return RIGHT;
    }
    // intersection rectangle is horizontal
    // --> collision is vertical
    else
    {
        // top side of IR coincides with top side of current rectangle
        if(interRect.top() == curr_rect.y())
            return UP;
        else
            return DOWN;
    }
}
