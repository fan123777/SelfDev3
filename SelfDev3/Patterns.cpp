#include "Patterns.h"
#include <chrono>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <iostream>

using namespace std;

namespace patterns
{
	void main()
	{
//		chapter1::main();
		chapter2::main();
//		chapter4::main();
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

		}

		// Window
		void Window::drawRect()
		{
		}

		// Rectangle
		void Rectangle::draw(Window* w)
		{
			w->drawRect();
		}

		// Composition
		Composition::Composition(Compositor* compositor)
			:mCompositor(compositor)
		{
			mCompositor->setComposition(this);
		}

		void Composition::insert(Glyph* g, int i)
		{
			Glyph::insert(g, i);
			mCompositor->Compose();
		}
	}

	namespace chapter4
	{
		void main()
		{

		}

		// CompositeEquipment
		Currency CompositeEquipment::netPrice()
		{
			Currency total = 0;
			for (auto& item : mEquipment)
				total += item->netPrice();
			return total;
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