#ifndef PATTERNS_H
#define PATTERNS_H

#include <map>
#include <string>
#include <set>
#include <iostream>
#include <list>
#include <atomic>
#include <mutex>
#include <thread>

namespace patterns
{
	void main();
	
	// 25.03.15
	// Chapter1. Introduction to Design Patterns

	// missing:
	// - paralel
	// - spread programing
	// - realtime systems

	// pattern properties:
	// - name
	// - task
	// - solution
	// - results

	// MVC model
	// subscription/notification
	// model -> views, when data changed
	// views get data from model.
	// MVC supports inserted views using CompositeView. Composite
	// Controller defines reaction on pressing buttons.
	// view uses Controller Child Object, to realise concrete reaction strategy. To change strategy change Controller.
	// View<->Controller is Strategy.
	// MVC also uses factory method, to set default controller.
	// Main relations - Observer, Composite, Strategy.

	// name
	// purpose
	// other names
	// motivation
	// applicability
	// structure
	// participants
	// relations
	// results
	// realisation
	// code example
	// applications
	// relaed patterns

	// generating, structure, behavior
	// class level - inheritance
	// object level - relations between objects.
	// generating class patterns often delegate responsability for object creation to subclasses.
	// -//- object - delegate to other object.
	// structural class - inheritance for class creation
	// -//- object - create object from parts
	// behaviour class - describe algorithm and controlling flow
	// -//- how works group of objects. 

	// abstraction leads to a flexible design
	// strategy - interchangeable families of algorithms
	// State - state as object
	// facade - subsystem as an object
	// - ---> The dotted line arrow indicates the class that instantiates objects of another class.
	// |
	// /\
	// |
	// - inheritance.
	// - Names of abstract classes are decorated in italics, also abstract operations are italic.
	// - mixin class, add new interface or functionality, mixin class is not for instancing.
	// type = interface of object.
	// interface inheritance = public to class with only virtual functions.
	// realisation inheritance  = private

	// 1. Develop oriented on interface, not on realisation.
	// use abstract things for variables type, not concrete objects.

	// inheritance and composition.
	// inheritance breaks incapsulation.
	// use abstract classes, they don't have realisation.
	// composition doesn't breake incapsulation.
	// 2. Prefer composition to class inheritance.

	// delegation, window is not rectangle, window containes rectangle, 
	// window::area(){return rectangle->area;}
	// easy composition in runtime
	// delegating best works in standard patterns: State, Strategy, Visitor.
	// you can always use composition instead of inheritance.

	// c++ templates.

	// aggregation and acquaintance
	// aggregation means that object owns another(same lifetime) romb -> - aggregation
	// acquaintance object knows about another object. -> - acquaintance

	// Planning for future changes
	// - create objects indirectly: Abstract Factory, Factory Method, prototype
	// - Depending on the specific operation: Chain of Responsibility, command
	// - Depending on the hardware and software platforms: Abstract Factory, Bridge
	// - dependence on the submission or implementation of the object: Abstract Factory, Bridge, guardian, deputy;
	// - Depending on the algorithm. Bridge, iterator, strategy, template method, the visitor;
	// - strong coupling : Abstract Factory, Bridge, a chain of responsibilities, the team, the facade, the mediator, the observer;
	// - expansion of functionality through subclassing. Use composition and delegation: Bridge, a chain of responsibilities, linker, decorator, observer, strategy;
	// - inconvenience when changing classes: Adapter, Decorator, the visitor.

	// - Frameworks for applications
	// frameworks should be as flexible and extensible.
	// difference between patterns and frameworks.
	// - design patterns are more abstract than frameworks.
	// - as architectural elements, design patterns are smaller than frames.
	// - design patterns are less specialized than frameworks.
	// Huge OOP applications are made of layers of frameworks.

	// to do:
	// - MVC model+:  Observer+, Composite+, Strategy+(!!!). Practice with MVC!!!
	// - reasons for redisigning (Planning for future changes)
	// - main rules of OOP
	// - inheritance, composition, delegating.
	// - interface inheritance
	// - realisation inheritance
	// - abstract classes.
	// - c++ templates
	// - aggregation and acquaintance
	// - create app with several dlls and several libs
	// - practice with it.

	namespace chapter1
	{
		void main();

		// MVC Model
		// three areas: processing, output, and input

		class Observer
		{
		public:
			virtual void update() = 0;
		};

		class Model
		{
		public:
			Model(const std::map<std::string, int>& partiesVotes);

			// access interface for modification by controller
			void clearVotes();
			void changeVote(const std::string& party, int vote);
			// factory functions for view access to data
			// ...

			void attach(Observer* o);
			void detach(Observer* o);

			// getters
			std::map<std::string, int> getVotes() const;

		protected:
			virtual void notify();

		private:
			std::map<std::string, int> mPartiesVotes;
			std::set<Observer*> mRegistry;
		};

		enum EventTypeEnum
		{
			EventTypeDefault = 0,
			EventTypeChangeVote = 1
		};

		class Event
		{
		public:
			Event(EventTypeEnum type = EventTypeDefault)
				:mEventType(type)
			{
			}

			EventTypeEnum getType() const
			{
				return mEventType;
			}

		private:
			EventTypeEnum mEventType;
		};

		class View;

		// If you plan to modify functionality, or if you want to provide reusable controllers and therefore would like the controller to be independent of a specific interface.apply the Command Processor (277) design pattern.
		class Controller : public Observer
		{
		public:
			virtual void handleEvent(Event*); // default  = no op

			Controller(View* v);

			virtual ~Controller();
			virtual void update(); // default  = no op

		protected:
			Model* mModel;
			View* mView;
		};

		// If the application allows dynamic opening and closing of views, it is a good idea to provide a comp.onent for managing open views.
		// Apply the View Handler(291) design pattern
		// Apply the Composite pattern[GHJV95] to create hierarchically composed views
		// Use the	Chain of Responsibility pattern IGHJV951 to manage this delegation of events
		// You may want to make these classes platform independen, use Bridje design pattern
		class View : public Observer
		{
		public:
			View(Model* m);
			virtual ~View();

			virtual void update();

			// abstract interface to be redifined
			virtual void draw();

			Model* getModel();

			Controller* getController();

			//c++ deficit: use initialize to call right factory method
			virtual void initialize();

			virtual Controller* makeController();

			virtual Controller* setController(Controller* c);

		protected:
			Model* mModel;
			Controller* mController;
		};

		class BarChartView : public View
		{
		public:
			BarChartView(Model* m);
			virtual void draw() override;
		};

		class TableView;

		class TableController : public Controller
		{
		public:
			TableController(TableView* tv);
			void handleEvent(Event* e) override;
		};

		class TableView : public View
		{
		public:
			TableView(Model* m);
			void draw() override;
			Controller* makeController() override;
		};

		// Variant: Document-View.
		// It is possible to base an application framework on this pattern
		// deactivate view, if deactivate controller.

		// Next: Observer, Composite, Strategy.
	}

	namespace chapter2
	{
		void main();
		// structure of the document
		// recursive composition

		class Window
		{
		public:
			void drawRect();
		};

		class Rect
		{

		};

		class Point
		{

		};

		class Glyph
		{
		public:
			virtual void draw(Window* w);
			virtual void bounds(Rect& r);
			virtual bool intersects(const Point& p);
			virtual void insert(Glyph* g, int i);
			virtual void remove(Glyph* g);
			virtual Glyph* child(int i);
			virtual Glyph* parent();
		};

		class Rectangle : public Glyph
		{
		public:
			void draw(Window* w) override;
			bool intersects(const Point& p) override;
		};

		class Character : public Glyph
		{
		public:
			void draw(Window* w) override;
			bool intersects(const Point& p) override;
		private:
			char c;
		};

		class Row : public Glyph
		{
		public:
			void draw(Window* w) override;
			bool intersects(const Point& p) override;
			void insert(Glyph* g, int i) override;
		};

		class Polygon : public Glyph
		{
		public:
			void draw(Window* w) override;
			bool intersects(const Point& p) override;
		};
	}

	namespace chapter4
	{
		void main();

		// ----------Composite----------
		// Use when
		// - need to introduce a hierarchy of objects types of part-whole
		// - want customers to consistently interpreted the components and individual objects
		// Results
		// - defines a class hierarchy, consisting of primitive and composite objects.
		// - simplifies the architecture of the client.
		// - makes it easy to add new kinds of components.
		// - contributes to the creation of the overall design.
		// Realisation
		// - explicit references to parents.
		// - separation of the components.
		// - Maximizing class interface Component.
		// - classified operations management descendants.
		// - Should Component implement a list of components.
		// - ordering descendants.
		// - caching to improve performance.
		// - who should remove components.
		// - what data structure is best suited for storage components.

		typedef int Watt;
		typedef int Currency;
		class Equipment;
		typedef std::list<Equipment*> ContainerType;
		typedef ContainerType::iterator ContainerTypeIterator;

		class Equipment
		{
		public:
			virtual ~Equipment();

			const std::string& getName();
			virtual Watt power();
			virtual Watt netPrice();
			virtual Currency discountPrice();

			virtual void add(Equipment* e);
			virtual void remove(Equipment* e);
		protected:
			Equipment(const std::string& name);
		private:
			std::string mName;
		};

		class FloppyDisk : public Equipment
		{
		public:
			FloppyDisk(const std::string& name);
			~FloppyDisk() override;
			Watt power() override;
			Currency netPrice() override;
			Currency discountPrice() override;
		};

		class CompositeEquipment : public Equipment
		{
		public:
			~CompositeEquipment() override;
			Watt power() override;
			Currency netPrice() override;
			Currency discountPrice() override;
			void add(Equipment* e) override;
			void remove(Equipment* e) override;
		protected:
			CompositeEquipment(const std::string& name);
		private:
			ContainerType mEquipment;
		};

		class Chassis : public CompositeEquipment
		{
		public:
			Chassis(const std::string& name);
			~Chassis() override;
			Watt power() override;
			Currency netPrice() override;
			Currency discountPrice() override;
		};

		//Related Patterns
		// - chain of responsibilities
		// - decorator
		// - visitor
		// !!! practise with composite
	}

	namespace chapter5
	{
		void main();

		// ----------Observer(dependents, publisher-subscriber)----------
		// Use when:
		// - 2 aspects, 1 depends on another
		// - after modifuing 1 object you need to modify some other
		// - objects mustn't be closely linked
		// Results:
		// - objects linked minimally
		// - support for broadcast communication
		// - unexpected updates
		// Realisation:
		// - mapping entities to observers.
		// - observation of more than one subject. We can pass object in update() parameter to identify.
		// - who initiates the update. unnecessary interim updates.
		// - Hanging links to remote entities.
		// - guarantees the consistency condition of the subject before sending the notification.
		// - how to avoid depending on the protocol updates from the observer: the model pulling and pushing. 
		// 2 possibilities. 1) push: send data in update(), 2) pull data after update recieved.
		// - explicit specifying modifications of interest.
		// void Subject::Attach(Observer*, Aspects interest); we can specify wich objects to update on some events.
		// than in update we send modified interest.
		// void Observer::Update(Subject*, Aspects interest);
		// - encapsulation complex update semantics.ChangeManager(mediator pattern)
		// - combining classes Subject and Observer.

		class Subject;

		class Observer
		{
		public:
			virtual ~Observer(){};
			virtual void update(Subject* theChangedSubject) = 0;
		protected:
			Observer(){};
		};

		class Subject
		{
		public:
			virtual ~Subject(){};
			virtual void attach(Observer* o);
			virtual void detach(Observer* o);
			virtual void notify();
		protected:
			Subject(){};
		private:
			std::list<Observer*> mObservers;
		};

		class ClockTimer : public Subject
		{
		public:
			ClockTimer();
			~ClockTimer();
			void start();
			void stop();

			std::string getCurrentTime() const;
			
		private:
			void tick();
			void run();

			int mSleepTimeMs;
			std::atomic<bool> mIsRunning;
			std::string mCurrentTime;
			mutable std::mutex mTimeMutex;
			std::thread mTimeThread;
		};

		class Widget
		{
		public:
			virtual void draw() = 0;
		};

		class DigitalClock : public Widget, public Observer
		{
		public:
			DigitalClock(ClockTimer* ct);
			virtual ~DigitalClock();

			void update(Subject* s) override;

			void draw() override;

		private:
			ClockTimer* mSubject;
		};


//		class AnalogClock : public Widget, public Observer
//		{
//
//		};

		//Related Patterns
		// - mediator
		// - singleton

		// ----------Strategy(Policy)----------
		// Use when:
		// - There are many related classes, differing only by the behavior.
		// - you need to have several different versions of the algorithm.
		// - the algorithm contains data on which the client does not have to "know".
		// - in the class defines many behaviors that represented branched conditional statements.
		// Results:
		// - family of related algorithms.
		// - alternative to subclassing.
		// - using strategies you can get rid of conditional statements.
		// - implementation choices.
		// - customers need to know about the various strategies.
		// - exchange of information between strategy and context.
		// - increasing the number of objects.
		// Realisation.
		// - definition of interfaces and classes Strategy Context.
		// - strategy as template parameters.
		// - objects strategy can not be set.

		class Compositor;
		class Component;

		class Composition
		{
		public:
			Composition(Compositor* c);
			void repair();

		private:
			Compositor * mCompositor;
			Component* mComponents;
			int mComponentCount;
			int mLineWidth;
			int mLineBreaks;
			int mLineCount;
		};

		class Coord
		{

		};

		class Compositor
		{
		public:
			virtual int Compose() = 0;
		protected:
			Compositor();
		};

		class SimpleCompositor : public Compositor
		{
		public:
			SimpleCompositor();
			int Compose() override;
		};

		class TeXCompositor : public Compositor
		{
		public:
			TeXCompositor();
			int Compose() override;
		};

		class ArrayCompositor : public Compositor
		{
		public:
			ArrayCompositor(int interval);
			virtual int Compose();
		};

		// Related:
		// - flyweight
	}
}

#endif /* PATTERNS_H */