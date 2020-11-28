#include "chaser.h"
#include "errors/gameerror.hh"

Chaser::Chaser()
{
    xSpeed_ = 0;
    ySpeed_ = 0;
    maxspeed_ = MAXSPEED;
    acceleration_ = ACCELERATION;
}

void Chaser::updateLocation(int hor, int ver)
{
    if (locationset_)
    {
        xSpeed_ += hor * acceleration_;
        if (xSpeed_ >= maxspeed_ or xSpeed_ <= -maxspeed_) {
            xSpeed_ -= hor * acceleration_;
        }
        ySpeed_ += ver * acceleration_;
        if (ySpeed_ >= maxspeed_ or ySpeed_ <= -maxspeed_) {
            ySpeed_ -= ver * acceleration_;
        }
        location_.setXY(location_.giveX() + xSpeed_, location_.giveY() + ySpeed_);
    } else
    {
        throw Interface::GameError("Starting location not set");
    }

}

void Chaser::chase(std::shared_ptr<Interface::IActor> target)
{
    Interface::Location targetloc = target->giveLocation();
    if (locationValid(targetloc))
    {
        if (targetloc.giveX() > location_.giveX()) {
            if (xSpeed_ <= maxspeed_) {
                xSpeed_ += acceleration_;
                positiveXMovement_ = true;
            }
        }
        else {
            if (xSpeed_ >= -maxspeed_) {
                xSpeed_ += -acceleration_;
                positiveXMovement_ = false;
            }
        }
        if (targetloc.giveY() > location_.giveY()) {
            if (ySpeed_ <= maxspeed_) {
                ySpeed_ += acceleration_;
                positiveYMovement_ = true;
            }
        }
        else {
            if (ySpeed_ >= -maxspeed_) {
                ySpeed_ += -acceleration_;
                positiveYMovement_ = false;
            }
        }
        location_.setXY(location_.giveX() + xSpeed_, location_.giveY() + ySpeed_);
    } else
    {
        throw Interface::GameError("Target location not set");
    }

}

bool Chaser::isClose(std::shared_ptr<Interface::IActor> target, int range)
{
    if (location_.isClose(target->giveLocation(), range)) {
        return true;
    }
    else {
        return false;
    }
}

Interface::Location Chaser::giveLocation() const
{
    if (locationset_)
    {
        return location_;
    } else {
        throw Interface::GameError("actor wasn't given a location");
    }

}

void Chaser::move(Interface::Location loc)
{
    if (not (locationValid(loc)))
    {
        location_ = loc;
        locationset_ = true;
    } else {
        throw Interface::GameError("Location is not possible");
    }

}

void Chaser::remove()
{
    removed_ = true;
}

bool Chaser::isRemoved() const
{
    return removed_;
}

void Chaser::setMaxSpeed(int maxspeed)
{
    maxspeed_ = maxspeed;
}

void Chaser::setAcceleration(int acceleration)
{
    acceleration_ = acceleration;
}

int Chaser::getDirection(std::shared_ptr<Interface::IActor> target)
{
    int direction;

    Interface::Location targetloc = target->giveLocation();

    if (abs(targetloc.giveX() - location_.giveX()) > abs(targetloc.giveY() - location_.giveY()) ){
        if (positiveXMovement_){
            direction = RIGHT;
        } else {
            direction = LEFT;
        }
    } else {
        if (positiveYMovement_){
            direction = DOWN;
        } else {
            direction = UP;
        }
    }

    return direction;
}

bool Chaser::locationValid(Interface::Location testloc)
{
    if (testloc.giveNorthernCoord() == 6700000 and testloc.giveEasternCoord() == 3500000) {
        return false;
    } else {
        return true;
    }
}
