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
#include <vector>
#include <memory>

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
	// - MVC model+:  Observer+, Composite+, Strategy+. Practice with MVC
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

		//*** Composite
		class Glyph;
		class Character;
		
		// Bridge
		class WindowImpl;
		class View;

		class Window
		{
		public:
			// control Windows
			virtual void redraw(){};
			virtual void raise(){};
			virtual void lower(){};
			virtual void iconify(){};
			virtual void deiconify(){};

			// graphics
			virtual void drawLine(){};
			void drawGlyph(Glyph* g);
			void drawRect(Glyph* g);
			void drawCharacter(Character* g);
		protected:
			WindowImpl* getWindowImp();
			View* getView();
		private:
			WindowImpl* mImp;
			View* mView;
		};

		class Rect
		{

		};

		class Point
		{

		};

		typedef std::shared_ptr<Glyph> ElementType;
		typedef std::vector<std::shared_ptr<Glyph>> ContainerType;
		typedef std::vector<std::shared_ptr<Glyph>>::iterator ContainerIteratorType;

		enum TraversalEnum
		{
			TraversalChildren = 0,
			TraversalPreorder = 1,
			TraversalPostOrder = 2,
			TraversalInorder = 3
		};

		// Iterator
		template<typename T>
		class Iterator
		{
		public:
			virtual void first() = 0;
			virtual void next() = 0;
			virtual bool isDone() = 0;
			virtual T* getCurrent() = 0;
		};

		template<typename T>
		class PreorderIterator : public Iterator<T>
		{
		public:
			PreorderIterator(Glyph* g);

			void first() override;
			void next() override;
			bool isDone() override;
			T* getCurrent() override;
		private:
			T* mElement;
		};

		template<typename T>
		class ArrayIterator : public Iterator<T>
		{
		public:
			ArrayIterator(Glyph* g);

			void first() override;
			void next() override;
			bool isDone() override;
			T* getCurrent() override;
		private:
			T* mElement;
		};

		template<typename T>
		class ListIterator : public Iterator<T>
		{
		public:
			ListIterator(Glyph* g);

			void first() override;
			void next() override;
			bool isDone() override;
			T* getCurrent() override;
		private:
			T* mElement;
		};

		template<typename T>
		class NullIterator : public Iterator<T>
		{
		public:
			void first() override{};
			void next() override{};
			bool isDone() override
			{
				return true;
			}
			T* getCurrent() override{ return nullptr; };
		};

		class SpellingChecker;

		class Glyph
		{
		public:
			virtual void draw(Window* w);
			virtual void bounds(Rect& r);
			virtual bool intersects(const Point& p);
			virtual void insert(ElementType g, int position);
			virtual void remove(int poosition);
			virtual ElementType child(int position);
			virtual ElementType parent();

			//void first(TraversalEnum kind);
			//void next();
			//bool isDone();
			//Glyph* getCurrent();
			//void insert(Glyph* g);
			Iterator<Glyph>* createIterator()
			{
				return new NullIterator<Glyph>();
			}

			//
			void checkMe(SpellingChecker& sc);
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
			Character(char c);
			void draw(Window* w) override;
			char c();
			void checkMe(SpellingChecker& sc);
		private:
			char mC;
		};

		class Composite : public Glyph
		{
		public:
			Composite();

			void draw(Window* w) override;
			void insert(ElementType g, int position) override;
			void remove(int position) override;
			ElementType child(int position) override;
			ElementType parent() override;

		private:
			ContainerType mChildren;
			ElementType mParent;
		};

		class Row : public Composite
		{
		public:
			void draw(Window* w) override;
			void insert(ElementType g, int position) override;
			void checkMe(SpellingChecker& sc);
		};

		class Polygon : public Composite
		{
		public:
			void draw(Window* w) override;
		};

		//*** Strategy
		class Compositor;

		class Composition : public Glyph
		{
		public:
			Composition(Compositor* compositor);

			void insert(std::shared_ptr<Glyph> g, int position) override;

		private:
			Compositor* mCompositor;
			// contains all visible glyphs.
		};

		class Compositor
		{
		public:
			void setComposition(Composition* c)
			{
				mComposition = c;
			};
			virtual void Compose(){};
		private:
			Composition* mComposition;
		};

		class SimpleCompositor : public Compositor
		{
		public:
			void Compose() override;
		};

		//*** Decorator
		class MonoGlyph : public Glyph
		{
		public:
			MonoGlyph(Glyph* component);
			void draw(Window* w) override;
		private:
			Glyph* mComponent;
		};

		class Border :public MonoGlyph
		{
		public:
			void draw(Window* w) override;
		private:
			void drawBorder(Window* w);
		};

		class Scroller :public MonoGlyph
		{
			
		};
		// unite bridge and abstract factory.

		// Bridge
		class Coord
		{

		};

		class WindowImp
		{
		public:
			virtual void impTop() = 0;
			virtual void impBottom() = 0;
			virtual void impSetExtentTop(const Point&) = 0;
			virtual void impSetOrigin(const Point&) = 0;

			virtual void deviceRect(Coord, Coord, Coord, Coord) = 0;
		protected:
			WindowImp();
		};

		class ApplicationWindow : public Window
		{
		public:
			virtual void drawContents();
		};

		// Command
		class Command
		{
		public:
			virtual void execute();
			virtual void unexecute();
			virtual bool reversible();
		};

		class PasteComand : public Command
		{
		public:
			void execute() override;
		private:
			std::string mData;
		};

		class MenuItem :public Glyph
		{
		public:
			void clicked();
		private:
			Command* mCommand;
		};

		// Visitor
		class SpellingChecker
		{
		public:
			virtual void checkCharacter(Character*);
			virtual void checkRow(Row*);

			const std::list<char> getMisspellings();

		protected:
			virtual bool isMisspelled(char c);

		private:
			char mCurrendWord;
			std::list<char> mMisspellings;
		};

		class Visitor
		{
		public:
			virtual void visitCharacter(Character*){};
			virtual void visitRow(Row*){};
		};
	}

	namespace chapter3
	{
		void main();

		enum DirectionEnum
		{
			North = 0,
			South = 1,
			East = 2,
			West = 3
		};

		class MapSite
		{
		public:
			virtual void enter() = 0;
		};

		class Room : public MapSite
		{
		public:
			Room(int roomNo);

			MapSite* GetSide(DirectionEnum direction) const;
			void setSide(DirectionEnum direction, MapSite* ms);

			void enter() override;
		private:
			MapSite* mSides[4];
			int mRoomNumber;
		};

		class Wall : public MapSite
		{
		public:

			void enter() override;
		};

		class Door : public MapSite
		{
		public:
			Door(Room* r1 = nullptr, Room* r2 = nullptr);

			void enter() override;
			Room* otherSideFromRoom(Room* other);

		private:
			Room* mRoom1;
			Room* mRoom2;
			bool mIsOpen;
		};

		class Maze
		{
		public:
			void AddRoom(Room* room);
			Room* roomNo(int) const;
		private:
		};

		class MazeFactory;

		class MazeGame
		{
		public:
			Maze* CreateMaze();
			Maze* CreateMaze(const MazeFactory& factory);
		};

		// Abstract Factory
		// Kit
		// Use when:
		// - the system should not depend on how created, assembled and presented to its constituent objects
		// - belonging to a family of related facilities should be used together, and you need to enforce this restriction;
		// - the system must be configured with one of the families of its constituent facilities;
		// - you want to present a library of objects, revealing only their interfaces, but not the implementation.
		// Results:
		// - isolates concrete classes.
		// - simplifies the replacement product families.
		// - ensure compatibility of products
		// - support a new kind of product is difficult.
		// Realisation:
		// - factory as objects that exist in a single copy.
		// - creating products.
		// - definition extensible factories.

		class MazeFactory
		{
		public:
			MazeFactory();

			virtual Maze* makeMaze() const;
			virtual Wall* makeWall() const;
			virtual Room* makeRoom(int n) const;
			virtual Door* makeDoor(Room* r1, Room* r2) const;
		};

		class EnchantedMazeFactory : public MazeFactory
		{
		public:
			EnchantedMazeFactory();

			Room* makeRoom(int n) const override;
			Door* makeDoor(Room* r1, Room* r2) const override;

		private:
			int castSpell() const;

		};

		class EnchantedRoom:public Room
		{
		public:
			EnchantedRoom(int n, int s);
		};

		class DoorNeedingSpell:public Door
		{
		public:
			DoorNeedingSpell(Room* r1 = nullptr, Room* r2 = nullptr);
		};
		// Abstract factory - set of factory methods.
		// Related patterns: factory method, prototype, singleton.
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
		// practise with composite

		// ----------Decorator----------
		// Wrapper
		// Use when:
		// - dynamically add new functionality (transparent to the client)
		// - to implement responsibilities
		// - when making subclasses is not convinient or possible.
		// Results:
		// +:
		// - more flexible then inheritance.
		// - avoids an overloaded function classes on the upper levels hierarchy.
		// -:
		// - decorator and its component aren't equel
		// - lots of small objects
		// Realisation
		// - interfaces of decorator and component must be equal.
		// - if only 1 additional functionality - no need in abstract decorator class.
		// - Component classes lightweight, component class should be interface.
		// - changes in appearance, but not the internal structure of the object.
		// - decorators are transparent for components.

		class VisualComponent
		{
		public:
			virtual ~VisualComponent();

			virtual void draw();
			virtual void resize();
		};

		class Decorator :public VisualComponent
		{
		public:
			Decorator(VisualComponent* vc);
			void draw() override;
			void resize() override;
		private:
			VisualComponent* mComponent;
		};

		class BorderDecorator : public Decorator
		{
		public:
			BorderDecorator(VisualComponent* vc, int width);
			void draw() override;
		private:
			void drawBorder(int width);
			int mWidth;
		};

		// Related patterns:
		// - adapter, compositor, strategy.

		// ----------Bridge----------
		// Handle/Body.
		// Use when:
		// - you want to avoid a permanent binding of abstraction to implementation.
		// - and abstraction, and implementation should be expanded with new subclasses.
		// - changes in the implementation of an abstraction should not affect customers that is, the client code does not have to be recompiled
		// - you want to completely hide from clients the realization of abstraction.
		// - the number of classes begins to grow rapidly
		// - you want to share an implementation between multiple objects (perhaps using reference counting), and this fact should be hidden from the client.
		// Results:
		// - separation of interface from implementation.
		// - Improved extensibility.
		// - Hiding implementation details from clients.
		// Realisation:
		// - Only one class Implementor.
		// - creating the right object Implementor. we can use abstract factory.
		// - separation of distributors.
		// Related:
		// - abstract factory.
		// see realisation in chapter 2.
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

		class Coord
		{

		};

		class Composition
		{
		public:
			Composition(Compositor* c);
			void repair();

		private:
			Compositor * mCompositor;
			std::list<Component*> mComponents;
			int mComponentCount;
			int mLineWidth;
			int mLineBreaks;
			int mLineCount;
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

		//TODO: practice with:
		// Composite +
		// Strategy: ...
		// Observer: ...
		// MVC: ...

		// Command.
		// (Action, transaction)
		// Use when:
		// - parameterized to perform the actions in the case of the menu items Menultem
		// - determine to queue and execute requests at different times.
		// - to support the abolition of the operations.
		// - support logging changes so they can be run again after the emergency stop system.
		// - structure based system high level operations built from primitive.
		// Relations:
		// - the client creates an object Concrete Command and sets it to the recipient;
		// - Invoker object stores the initiator ConcreteCommand;
		// - the initiator sends a request, causing the operation command Execute. if supported the abolition of the executed actions, ConcreteCommand before calling Execute saves state information sufficient for rollback;
		// - ConcreteCommand operation object is the recipient for the request.
		// Results:
		// - command breaks the connection between the object of initiating the operation, and the object that has information on how to execute it;
		// - Commands - are very real objects. Allowed to manipulate them and expand them in the same way as with any other objects;
		// - simple commands, you can gather the components, such as the class of Macro Command, discussed above. In general, the compound commands described layout pattern;
		// - easy to add new commands, as no existing classes do not need to change.
		// Realisation:
		// - how "smart" should be a command.
		// - Support undo and redo operations.
		// - how to avoid accumulation of errors in the process of cancel.
		// - the use of templates in C++.
		
		class Command
		{
		public:
			virtual ~Command(){};
			virtual void execute() = 0;
		protected:
			Command(){};
		};

		class Document
		{
		public:
			Document(const std::string& name){};
			void open(){};
			void paste(){};
		};

		class Application
		{
		public:
			void addDocument(Document* document){};
		};

		class OpenCommand : public Command
		{
		public:
			OpenCommand(Application* app);
			void execute() override;
		protected:
			virtual const std::string& askUser();
		private:
			Application* mApplication;
			std::string mResponse;
		};

		class PasteCommand : public Command
		{
		public:
			PasteCommand(Document* document);
			void execute() override;
		private:
			Document* mDocument;
		};

		template<typename Receiver>
		class SimpleCommand:public Command
		{
		public:
		//	typedef void (Receiver::* r Action)();
		//	SimpleCommand(Receiver* r, Action a)
		//		:mReceiver(r), mAction(a)
		//	{

		//	}

		//	void execute() override
		//	{
		//		mReceiver->*mAction();
		//	}

		//private:
		//	Action mAction;
		//	Receiver* mReceiver;
		};

		class MacroCommand : public Command
		{
		public:
			MacroCommand();
			virtual ~MacroCommand();
			virtual void add(Command*);
			virtual void remove(Command*);
			void execute() override; // execute all commands from the list
		private:
			std::list<Command*> mCommands;
		};
		// Related patterns:
		// composition, memento, prototype.

		// Iterator(Cursor)
		// Use when:
		// - to access the content of aggregated objects without disclosing their internal representation;
		// - to support multiple active rounds of the same aggregated object
		// - to provide a uniform interface to bypass various aggregate structures(that is, to support polymorphic iteration)
		// Results:
		// - It supports various types of bypass unit.
		// - iterators simplify the interface of a class Aggregate.
		// - while for the unit can be active for several rounds.
		// Realization:
		// - what party controls the iteration.
		// - that defines the traversal algorithm.
		// - how stable is iterator.
		// - additional operations iterator.
		// - use polymorphic iterators in C++.
		// - iterators can have privileged access.
		// - iterators for composite objects.
		// - empty iterators. - use for composite objects.

		template<typename Item>
		class List
		{
		public:
			List(long size);
			long count() const;
			Item& get(long index) const;
		};

		template<typename Item>
		class Iterator
		{
		public:
			virtual void first() = 0;
			virtual void next() = 0;
			virtual bool isDone() const = 0;
			virtual Item current() const = 0;
		protected:
			Iterator();
		};

		template<typename Item>
		class ListIterator : public Iterator < Item >
		{
		public:
			ListIterator(const List<Item>* list)
				:mList(list),
				mCurrent(0)
			{
			}

			void first() override
			{
				mCurrent = 0;
			}

			void next() override
			{
				mCurrent++;
			}

			bool isDone() const override
			{
				return mCurrent >= mList->count();
			}

			Item current() const override
			{
				if (isDone())
					throw "Iterator out of bounds";
				return mList->get(mCurrent);
			}

		private:
			const List<Item>* mList;
			long mCurrent;
		};

		class Employee
		{
		public:
			void print()
			{
			}
		};

		void printEmployees(Iterator<Employee*>& i);

		template<typename T>
		class AbstractList
		{
		public:
			virtual Iterator<T>* CreateIterator() const = 0;
		};

		template<typename T>
		class IteratorPtr
		{
		public:
			IteratorPtr(Iterator<T>* i)
				:mI(i)
			{}

			~IteratorPtr()
			{
				delete mI;
			}

			Iterator<T>* operator->()
			{
				return mI;
			}

			Iterator<T>& operator*()
			{
				return *mI;
			}

		private:


		private:
			Iterator<T>* mI;
		};
		// Related patterns: compositor, factory method, memento.
		
		// Visitor.
		// Use when:
		// - 
	}

	namespace chapter6
	{
		void main();

		// additional info

		// Template method
		class Algorithm
		{
		public:
			virtual ~Algorithm();
			void doWork();
			
		protected:
			virtual void doPart1();
			virtual void doPart2();
			virtual void doPart3();
		};

		class MyAlgorithm : public Algorithm
		{
		protected:
			void doPart1() override;
		};

		// Alternatives to virtual functions:
		class GameCharacter
		{
		public:
			virtual void healthValue() const; 
		};
		// Template method with non virtual interface.
		class GameCharacter1
		{
		public:
			void healthValue();
		protected:
			virtual void doHealthValue() const;
		};
		// Strategy with function pointers
		class GameCharacter2;

		int defaultHealthCalc(const GameCharacter2& gc);

		class GameCharacter2
		{
		public:
			typedef int(*HealthCalcFunc)(const GameCharacter2& gc);

			explicit GameCharacter2(HealthCalcFunc hfc = defaultHealthCalc)
				:healthFunc(hfc)
			{
			}

			int healthValue() const
			{
				return healthFunc(*this);
			}

		private:
			HealthCalcFunc healthFunc;
		};

		// different objects can have different calculation function.
		// it can be changed in runtime.

		// pattern Strategy usinng std::function.
		class GameCharacter3
		{
		public:
			typedef std::function<int(const GameCharacter3&)> HealthCalcFunc;
			explicit GameCharacter3(HealthCalcFunc hfc = defaultHealthCalc)
				:healthFunc(hfc)
			{
			}

			int healthValue() const
			{
				return healthFunc(*this);
			}

		private:
			HealthCalcFunc healthFunc;
		};

		// classical Strategy
		class GameCharacter4;

		class HealthCalcFunc
		{
		public:
			virtual int calc(const GameCharacter4& gc) const;
		};

		class MyHcf : public HealthCalcFunc
		{
		public:
			int calc(const GameCharacter4& gc) const override;
		};

		class GameCharacter4
		{
		public:
			explicit GameCharacter4(HealthCalcFunc* hcf)
				:mHcf(hcf)
			{}

			int healthValue() const
			{
				return mHcf->calc(*this);
			}

		private:
			HealthCalcFunc* mHcf;
		};
	}
}

#endif /* PATTERNS_H */