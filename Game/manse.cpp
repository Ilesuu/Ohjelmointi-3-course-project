#include "manse.h"

Manse::Manse()
{
    gamestarted_ = false;
}

void Manse::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    //Currently test implementation in main, implementation here probably later
}

void Manse::setClock(QTime clock)
{
    time_ = clock;
}

void Manse::startGame()
{
    gamestarted_ = true;
}

bool Manse::isGameOver() const
{

}

void Manse::addStop(std::shared_ptr<Interface::IStop> stop)
{

}

void Manse::addActor(std::shared_ptr<Interface::IActor> newactor)
{

}

void Manse::removeActor(std::shared_ptr<Interface::IActor> actor)
{

}

void Manse::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{

}

bool Manse::findActor(std::shared_ptr<Interface::IActor> actor) const
{

}

void Manse::actorMoved(std::shared_ptr<Interface::IActor> actor)
{

}

std::vector<std::shared_ptr<Interface::IActor> > Manse::getNearbyActors(Interface::Location loc) const
{

}
