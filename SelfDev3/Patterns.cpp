#include "Patterns.h"
#include <chrono>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <iostream>
#include <cassert>

using namespace std;

namespace patterns
{
	void main()
	{
//		chapter1::main();
		chapter2::main();
		chapter3::main();
		chapter4::main();
//		chapter5::main();
		chapter6::main();
	}

	namespace chapter1
	{
		void main()
		{
			// initialize model
			std::map<std::string, int> partiesVotes;
			typedef std::map<std::string, int>::value_type partiesVotesType;
			partiesVotes.insert(partiesVotesType("red", 20));
			partiesVotes.insert(partiesVotesType("green", 30));
			partiesVotes.insert(partiesVotesType("blue", 40));
			Model m(partiesVotes);

			// initialize views
			TableView* v1 = new TableView(&m);
			v1->initialize();
			BarChartView* v2 = new BarChartView(&m);
			v2->initialize();
			// open another read-only table view;
			TableView *v3 = new TableView(&m);
			v3->initialize();

			v1->draw();

			auto c = v1->getController();
			Event e(EventTypeChangeVote);
			c->handleEvent(&e);

			// example for changing controller
			delete v1->setController(new TableController(v1));

			delete v3->setController(new Controller(v3)); // make v3 read-only

			c = v1->getController(); // since we deleted it's Controller
			c->handleEvent(&e);
		}

		// Observer
		void Observer::update()
		{

		}

		// Model
		Model::Model(const std::map<std::string, int>& partiesVotes)
			:mPartiesVotes(partiesVotes)
		{
		}

		void Model::clearVotes()
		{
			mPartiesVotes.clear();
			notify();
		}

		void Model::changeVote(const std::string& party, int vote)
		{
			mPartiesVotes[party] = vote;
			notify();
		}

		void Model::attach(Observer* o)
		{
			mRegistry.insert(o);
		}

		void Model::detach(Observer* o)
		{
			mRegistry.erase(o);
		}

		std::map<std::string, int> Model::getVotes() const
		{
			return mPartiesVotes;
		}

		void Model::notify()
		{
			// call update for all observers
			for (auto obs : mRegistry)
				obs->update();
		}

		// Controller
		void Controller::handleEvent(Event*){} // default  = no op

		Controller::Controller(View* v)
			:mView(v)
		{
			mModel = mView->getModel();
			mModel->attach(this);
		}

		Controller::~Controller()
		{
			mModel->detach(this);
		}

		void Controller::update(){} // default  = no op

		// View
		View::View(Model* m) :
			mModel(m),
			mController(nullptr)
		{
			mModel->attach(this);
		}

		View::~View()
		{
			mModel->detach(this);
		}

		void View::update()
		{
			draw();
		}

		void View::draw()
		{

		}

		Model* View::getModel()
		{
			return mModel;
		}

		Controller* View::getController()
		{
			return mController;
		}

		void View::initialize()
		{
			mController = makeController();
		}

		Controller* View::makeController()
		{
			return new Controller(this);
		}

		Controller* View::setController(Controller* c)
		{
			auto currentController = mController;
			mController = c;
			return currentController;
		}

		// BarChartView
		BarChartView::BarChartView(Model* m)
			:View(m)
		{}

		void BarChartView::draw()
		{
			auto data = mModel->getVotes();
			std::cout << "BarChartView::draw()\n";
			for (auto& pair : data)
				cout << pair.first << " : " << pair.second << endl;
		}

		// TableController
		TableController::TableController(TableView* tv)
			:Controller(tv)
		{
		}

		void TableController::handleEvent(Event* e)
		{
			// ... interpret event e
			// 
			// mModel->changeVote()
			if (e->getType() == EventTypeChangeVote)
			{
				mModel->changeVote("red", 50);
			}
		}

		// TableView
		TableView::TableView(Model* m)
			:View(m)
		{

		}

		void TableView::draw()
		{
			auto data = mModel->getVotes();
			cout << "TableView::draw()\n";
			for (auto& pair : data)
				cout << pair.first << " : " << pair.second << endl;
		}

		Controller* TableView::makeController()
		{
			return new TableController(this);
		}
	}

	namespace chapter2
	{
		void main()
		{
			Window w;

			//*** Composite
			Row row;
			shared_ptr<Character> c1(new Character('a'));

			shared_ptr<Polygon> p(new Polygon);
			shared_ptr<Character> c2(new Character('b'));
			shared_ptr<Character> c3(new Character('c'));
 			p->insert(c2, 0);
			p->insert(c3, 1);

			row.insert(c1, 0);
			row.insert(p, 1);

			row.draw(&w);

			// Strategy...
		}

		//*** Composite
		// Window
		void Window::drawRect(Glyph* g)
		{
			cout << "Window::drawRect" << endl;
		}

		void Window::drawGlyph(Glyph* g)
		{
			cout << "Window::drawGlyph" << endl;
		}

		void Window::drawCharacter(Character* g)
		{
			cout << "Window::drawCharacter(" << g->c() << ")" << endl;
		}

		// Glyph
		void Glyph::draw(Window* w)
		{
			w->drawGlyph(this);
			cout << "" << endl;
		}

		void Glyph::bounds(Rect& r)
		{
			cout << " Glyph::draw" << endl;
		}

		bool Glyph::intersects(const Point& p)
		{
			cout << "Glyph::intersects" << endl;
			return false;
		}

		void Glyph::insert(ElementType g, int position)
		{
			cout << "Glyph::insert" << endl;
		}

		void Glyph::remove(int position)
		{
			cout << "Glyph::remove" << endl;
		}

		std::shared_ptr<Glyph> Glyph::child(int position)
		{
			cout << "Glyph::child" << endl;
			return nullptr;
		}

		std::shared_ptr<Glyph> Glyph::parent()
		{
			cout << "Glyph::parent" << endl;
			return nullptr;
		}

		// Character
		Character::Character(char c)
			:mC(c)
		{}

		void Character::draw(Window* w)
		{
			w->drawCharacter(this);
		}

		char Character::c()
		{
			return mC;
		}

		// Rectangle
		void Rectangle::draw(Window* w)
		{
			w->drawRect(this);
		}

		// Composite
		Composite::Composite()
			:mParent(nullptr)
		{

		}

		void Composite::draw(Window* w)
		{
			cout << "Composite::draw" << endl;
			for (auto& child : mChildren)
				child->draw(w);
		}

		void Composite::insert(ElementType g, int position)
		{
			cout << "Composite::insert" << endl;
			assert(position >= 0 && position <= mChildren.size());
			mChildren.insert (mChildren.begin() + position, g);
		}

		void Composite::remove(int position)
		{
			cout << "Composite::remove" << endl;
			assert(position >= 0 && position <= mChildren.size());
			mChildren.erase(mChildren.begin() + position);
		}

		ElementType Composite::child(int position)
		{
			cout << "Composite::child" << endl;
			assert(position >= 0 && position <= mChildren.size());
			return mChildren[position];
		}

		ElementType Composite::parent()
		{
			cout << "Composite::parent" << endl;
			return mParent;
		}

		// Row
		void Row::draw(Window* w)
		{
			cout << "Row::draw" << endl;
			Composite::draw(w);
		}

		void Row::insert(ElementType g, int position)
		{
			cout << "Row::insert" << endl;
			Composite::insert(g, position);
		}

		// Polygon
		void Polygon::draw(Window* w)
		{
			cout << "Polygon::draw" << endl;
			Composite::draw(w);
		}

		// ***Strategy

		// Composition
		Composition::Composition(Compositor* compositor)
			:mCompositor(compositor)
		{
			mCompositor->setComposition(this);
		}

		void Composition::insert(ElementType g, int position)
		{
			Glyph::insert(g, position);
			mCompositor->Compose();
		}

		//*** Decorator
		// MonoGlyph
		MonoGlyph::MonoGlyph(Glyph* component)
			:mComponent(component)
		{
		}

		void MonoGlyph::draw(Window* w)
		{
			mComponent->draw(w);
		}

		// Border
		void Border::draw(Window* w)
		{
			MonoGlyph::draw(w);
			drawBorder(w);
		}

		void Border::drawBorder(Window* w)
		{

		}
	}

	namespace chapter3
	{
		void main()
		{

		}
		// Room
		Room::Room(int roomNo)
			:mRoomNumber(roomNo)
		{

		}

		void Room::setSide(DirectionEnum direction, MapSite* ms)
		{
			mSides[direction] = ms;
		}

		void Room::enter()
		{

		}

		// Wall
		void Wall::enter()
		{

		}

		// Door
		Door::Door(Room* r1, Room* r2)
			:mRoom1(r1),
			mRoom2(r2)
		{

		}

		void Door::enter()
		{

		}

		// Maze
		void Maze::AddRoom(Room* room)
		{

		}

		// MazeGame
		Maze* MazeGame::CreateMaze()
		{
			Maze* aMaze = new Maze;

			Room* r1 = new Room(1);
			Room* r2 = new Room(2);
			Door* theDoor = new Door(r1, r2);

			aMaze->AddRoom(r1);
			aMaze->AddRoom(r2);

			r1->setSide(North, new Wall);
			r1->setSide(East, theDoor);
			r1->setSide(South, new Wall);
			r1->setSide(West, new Wall);

			return aMaze;
		}

		// MazeFactory
		MazeFactory::MazeFactory()
		{

		}

		Maze* MazeFactory::makeMaze() const
		{
			return new Maze;
		}

		Wall* MazeFactory::makeWall() const
		{
			return new Wall;
		}

		Room* MazeFactory::makeRoom(int n) const
		{
			return new Room(n);
		}

		Door* MazeFactory::makeDoor(Room* r1, Room* r2) const
		{
			return new Door(r1, r2);
		}

		Maze* MazeGame::CreateMaze(const MazeFactory& factory)
		{
			Maze* aMaze = factory.makeMaze();

			Room* r1 = factory.makeRoom(1);
			Room* r2 = factory.makeRoom(2);
			Door* theDoor = factory.makeDoor(r1, r2);

			aMaze->AddRoom(r1);
			aMaze->AddRoom(r2);

			r1->setSide(North, new Wall);
			r1->setSide(East, theDoor);
			r1->setSide(South, new Wall);
			r1->setSide(West, new Wall);

			return aMaze;
		}

		// EnchantedMazeFactory
		EnchantedMazeFactory::EnchantedMazeFactory()
		{

		}

		Room* EnchantedMazeFactory::makeRoom(int n) const
		{
			return new EnchantedRoom(n, castSpell());
		}

		int EnchantedMazeFactory::castSpell() const
		{
			return 0;
		}

		Door* EnchantedMazeFactory::makeDoor(Room* r1, Room* r2) const
		{
			return new DoorNeedingSpell(r1, r2);
		}

		EnchantedRoom::EnchantedRoom(int n, int s)
			:Room(n)
		{

		}

				DoorNeedingSpell::DoorNeedingSpell(Room* r1, Room* r2)
		{

		}
		
	}

	namespace chapter4
	{
		void main()
		{
			// Decorator
			VisualComponent* vc = new VisualComponent;
			VisualComponent* borderedVCs = new BorderDecorator(vc, 5);
			delete borderedVCs;
			delete vc;
		}

		// CompositeEquipment
		Currency CompositeEquipment::netPrice()
		{
			Currency total = 0;
			for (auto& item : mEquipment)
				total += item->netPrice();
			return total;
		}

		// Decorator
		// VisualComponent
		VisualComponent::~VisualComponent()
		{

		}

		void VisualComponent::draw()
		{
			cout << "VisualComponent::draw()\n";
		}

		void VisualComponent::resize()
		{
			cout << "VisualComponent::resize()\n";
		}

		// Decorator
		Decorator::Decorator(VisualComponent* vc)
			:mComponent(vc)
		{
		}

		void Decorator::draw()
		{
			cout << "Decorator::draw()\n";
			mComponent->draw();
		}

		void Decorator::resize()
		{
			cout << "Decorator::resize()\n";
			mComponent->draw();
		}

		// BorderDecorator
		BorderDecorator::BorderDecorator(VisualComponent* vc, int width)
			:Decorator(vc),
			mWidth(width)
		{
		}

		void BorderDecorator::draw()
		{
			cout << "BorderDecorator::draw()\n";
			Decorator::draw();
			drawBorder(mWidth);
		}
	
		void BorderDecorator::drawBorder(int width)
		{
			cout << "BorderDecorator::drawBorder()\n";
		}

	}

	namespace chapter5
	{
		void main()
		{
			// Observer
			ClockTimer ct;
			DigitalClock dc(&ct);
			ct.start();
			this_thread::sleep_for(chrono::seconds(10));
			ct.stop();

			// Strategy
//			Composition* quick = new Composition(new SimpleCompositor);
//			Composition* slick = new Composition(new TeXCompositor);
//			Composition* iconic = new Composition(new ArrayCompositor(100));
		}

		// Observer
		// Subject
		void Subject::attach(Observer* o)
		{
			mObservers.push_back(o);
		}

		void Subject::detach(Observer* o)
		{
			mObservers.remove(o);
		}

		void Subject::notify()
		{
			for (auto& item : mObservers)
				item->update(this);
		}

		// ClockTimer
		ClockTimer::ClockTimer()
			:mSleepTimeMs(1000)
		{
			mIsRunning.store(false);
		}

		ClockTimer::~ClockTimer()
		{
			if (mTimeThread.joinable())
				mTimeThread.join();
		}

		void ClockTimer::start()
		{
			mCurrentTime.clear();
			mIsRunning.store(true);
			mTimeThread = thread(&ClockTimer::run, this);
		}

		void ClockTimer::stop()
		{
			mIsRunning.store(false);
		}

		std::string ClockTimer::getCurrentTime() const
		{
			string time;
			{
				lock_guard<mutex> lk(mTimeMutex);
				time = mCurrentTime;
			}
			return time;
		}

		void ClockTimer::tick()
		{
			notify();
		}

		void ClockTimer::run()
		{
			while (mIsRunning.load())
			{
				std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
				std::time_t t = std::chrono::system_clock::to_time_t(p);
				{
					lock_guard<mutex> lk(mTimeMutex);
					mCurrentTime = ctime(&t);
				}
				tick();
				this_thread::sleep_for(chrono::milliseconds(mSleepTimeMs));
			}
		}

		// DigitalClock
		DigitalClock::DigitalClock(ClockTimer* ct)
			:mSubject(ct)
		{
			mSubject->attach(this);
		}

		DigitalClock::~DigitalClock()
		{
			mSubject->detach(this);
		}

		void DigitalClock::update(Subject* theChangedSubject)
		{
			if (theChangedSubject == mSubject)
				draw();
		}

		void DigitalClock::draw()
		{
			cout << mSubject->getCurrentTime();
			// ...

			// draw digital watch
		}

		// Strategy
		void Composition::repair()
		{
			mCompositor->Compose();
		}
	}

	namespace chapter6
	{
		void main()
		{

		}

		// Template method
		void Algorithm::doWork()
		{
			doPart1();
			doPart2();
			doPart3();
		}

		void Algorithm::doPart1()
		{

		}

		void Algorithm::doPart2()
		{

		}

		void Algorithm::doPart3()
		{

		}
	}
}