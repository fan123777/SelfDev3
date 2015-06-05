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

		class Rectangle
		{
		public:
			int area();
		private:
			int mWidth;
			int mHeight;
		};

		class Window
		{
		public:
			Window(Rectangle* r);

			int area();

		private:
			Rectangle* mR;
		};
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
			void drawRect(int x0, int x1, int y0,int y1);
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

		struct Point
		{
			int x;
			int y;
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
			virtual ~Glyph();

			virtual void draw(Window* w);
			virtual void bounds(Rect& r);
			virtual bool intersects(const Point& p);
			virtual void insert(ElementType g, int position);
			virtual void remove(int position);
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

		// Abstract Factory.
		class ScrollBar : public Glyph
		{
		public:
			virtual void ScrollTo(int);
		};

		class Button : public Glyph
		{
		public:
			virtual void press();
		};

		class Menu : public Glyph
		{
		public:
			virtual void popup();
		};

		class GUIFactory
		{
		public:
			virtual ScrollBar* createScrollBar();
			virtual Button* createButton();
			virtual Menu* createMenu();
		};

		class Rectangle : public Glyph
		{
		public:
			void draw(Window* w) override;
			bool intersects(const Point& p) override;
		private:
			int mX0;
			int mX1;
			int mY0;
			int mY1;
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
			Wall(){}
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
			Maze* clone()
			{
				return new Maze(*this);
			}

			// if need some additional informarmation after cloning.
			virtual void initialize()
			{

			}

		private:
		};

		class MazeFactory;

		class MazeBuilder;

		class MazeGame
		{
		public:
			Maze* CreateMaze();
			Maze* CreateMaze(const MazeFactory& factory);
			Maze* CreateMaze(MazeBuilder& builder);

			// factory methods
			virtual Maze* MakeMaze() const
			{ return new Maze; }
			virtual Room* MakeRoom(int n) const
			{ return new Room(n);}
			virtual Wall* MakeWall() const
			{ return new Wall; }
			virtual Door* MakeDoor(Room* rl, Room* r2) const
			{return new Door(rl, r2);}

			Maze* makeMaze();

		};

		// Abstract Factory
		// Kit
		// Motivation:
		class Window
		{

		};

		class PMWindow : public Window
		{

		};

		class MotifWindow : public Window
		{

		};

		class ScrollBar
		{

		};

		class PMScrollBar : public ScrollBar
		{

		};

		class MotifScrollBar : public ScrollBar
		{

		};

		class WidgetFactory
		{
		public:
			virtual ScrollBar* createScrollBar() = 0;
			virtual Window* createWindow() = 0;
		};

		class MotifWidgetFactory : public WidgetFactory
		{
		public:
			ScrollBar* createScrollBar() override;
			Window* createWindow() override;
		};

		class PMWidgetFactory : public WidgetFactory
		{
		public:
			ScrollBar* createScrollBar() override;
			Window* createWindow() override;
		};
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
		// Example:
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

		// MazeFactory is concrete class.
		// Abstract factory - set of factory methods.
		// Related patterns: factory method, prototype, singleton.

		// Builder
		// Motivation:
		class TextConverter
		{
		public:
			virtual void convertCharacter();
			virtual void convertFontChange();
			virtual void convertParagraph();
		};

		class ASCIIConverter :public TextConverter
		{
		public:
			void convertCharacter() override;
			void getASCIIText();
		};

		class TeXConverter :public TextConverter
		{
		public:
			void convertCharacter() override;
			void convertFontChange() override;
			void convertParagraph() override;
			void getTeXText();
		};

		class TextWidgetConverter :public TextConverter
		{
		public:
			void convertCharacter() override;
			void convertFontChange() override;
			void convertParagraph() override;
			void getTextWidget();
		};

		class RTFReader
		{
		public:
			void parseRTF();
		private:
			TextConverter* builder;
		};
		// Use wwhen:
		// - algorithm for creating a complex object should not depend on which parts of an object is and how they are joined together
		// - the design process should provide different views of the constructed object
		// Results:
		// - It allows you to change the internal representation of the product.
		// - It isolates the code that implements the design and performance.
		// - It gives finer control over the design process.
		// Realization:
		// - interface design and assembly.
		// - why not an abstract class for products.
		// - empty methods class Builder by default.

		class MazeBuilder
		{
		public:
			virtual void buildMaze(){};
			virtual void buildRoom(int){};
			virtual void buildDoor(int, int){};
			virtual Maze* getMaze()
			{
				return nullptr;
			}
		};

		class StandardMazeBuilder : public MazeBuilder
		{
		public:
			StandardMazeBuilder()
			{
				currentMaze = nullptr;
			}

			void buildMaze() override
			{
				currentMaze = new Maze;
			}
			void buildRoom(int) override
			{

			}
			void buildDoor(int, int) override
			{

			}
			Maze* getMaze() override
			{
				return currentMaze;
			}

		private:
			DirectionEnum commonWall(Room*, Room*);
			Maze* currentMaze;
		};
		// Related patterns: abstract factory, compositor.

		// Factory method.
		// virtual constructor.

		class Document
		{
		public:
			virtual ~Document();

			virtual void open() = 0;
			virtual void close() = 0;
			virtual void save() = 0;
			virtual void revert() = 0;
		};

		class Application
		{
		public:
			virtual ~Application();

			virtual Document* createDocument() = 0;
			virtual void openDocument() = 0;
			virtual void newDocument() = 0;
		};

		class MyDocument :public Document
		{
		public:
			void open() override{}
			void close() override{}
			void save() override{}
			void revert() override{}
		};

		class MyApplication : public Application
		{
		public:
			Document* createDocument() override
			{
				return new MyDocument();
			}

			void openDocument() override
			{

			}

			void newDocument() override
			{
				mDocuments.push_back(new MyDocument);
			}

		private:
			std::list<Document*> mDocuments;
		};
		// Use when:
		// - the class is not known beforehand, objects which classes it is necessary to create.
		// - Class is designed so that objects that it creates, specify subclasses
		// - class delegate their responsibilities to one of several subsidiary subclasses
		// Results:
		// - It provides subclasses operations hooks
		// - connects parallel hierarchies
		// Realization:
		// - two main types of pattern
		// - parameterized factory methods
		// - language-dependent variations and problems.
		// - You have to be careful not to cause the factory methods in the class constructor Creator: at this moment the factory method in a derived class ConcreteCreator not yet available.
		// - Use templates to avoid subclassing.
		// - naming conventions.
		// Related Patterns: abstract factory, template method(new document), Prototype.

		// Prototype.
		class Graphic
		{
		public:
			virtual ~Graphic();
			virtual void draw();
			virtual Graphic* clone();
		};

		class Staff : public Graphic
		{
		public:
			void draw() override;
			Graphic* clone() override;
		};

		class MusicalNote : public Graphic
		{

		};

		class WholeNote : public MusicalNote
		{
		public:
			void draw() override;
			Graphic* clone() override
			{
				return new WholeNote(*this);
			}
		};

		class Tool
		{
		public:
			virtual ~Tool();
			virtual void manipulate() = 0;
		};

		class RotateTool :public Tool
		{
		public:
			void manipulate() override;
		};

		class GraphicTool : public Tool
		{
		public:
			void manipulate() override
			{

			}
		private:
			Graphic* prototype;
		};
		// Use when:
		// - instantiated classes are defined at run time, for example, by dynamic loading.
		// - in order to avoid constructing class hierarchies, or factories, parallel class hierarchy of products.
		// - instances may be in one of the not very large number of different states.
		// Results:
		// - adding and removing products at runtime.
		// - specification of new objects by varying values.
		// - Specifying new objects by varying structure.
		// - reducing the number of subclasses.
		// - dynamic configuration application classes.
		// Realization.
		// - Use the controller prototyping.
		// - implementation of clone operation.
		// - Initialization clones.
		class MazePrototypeFactory : public MazeFactory
		{
		public:
			MazePrototypeFactory(Maze* m, Wall* w, Room* r, Door* d)
				:prototypeMaze(m),
				prototypeWall(w),
				prototypeRoom(r),
				prototypeDoor(d)
			{
			}

			Maze* makeMaze() const override
			{
				return prototypeMaze->clone();
				return new Maze;
			}
			Wall* makeWall() const override;
			Room* makeRoom(int n) const override;
			Door* makeDoor(Room* r1, Room* r2) const override;

		private:
			Maze* prototypeMaze;
			Room* prototypeRoom;
			Wall* prototypeWall;
			Door* prototypeDoor;
		};
		// Related Patterns: abstract factory, compositor, decorator.

		// Singleton.
		// Use when:
		// - must be exactly one instance of a class, readily available to all customers;
		// - only copy should expand by generating subclasses, and customers need to be able to work with an expanded instance without modifying their code
		// Results:
		// - controlled access to a single copy.
		// - decrease in the number of names.
		// - allows specification of operations and presentation.
		// - allows a variable number of copies.
		// - greater flexibility than class operations.
		// Realization:
		// - guaranteeing a single instance.
		// in C ++ is not determined by the order of constructor calls for global objects across borders translation units.It means that generating patterns among solitary there can be no dependencies. if they are, mistakes are inevitable.
		// - subclassing Singleton.

		class MazeFactorySingleton
		{
		public:
			static MazeFactorySingleton* Instance();
		protected:
			MazeFactorySingleton()
			{
			}
		private:
			static MazeFactorySingleton* instance;
		};
		// Related patterns: abstract factory, builder, prototype.

		// Discussion of generating patterns
		// You can use factory method first, but if you see then it is not good, use others.
	}

	namespace chapter4
	{
		void main();

		// Adapter
		// Wrapper.
		// Use when:
		// - You want to use an existing class, but its interface does not match your needs;
		// - going to create a reusable class that must interact with the unknown in advance or related classes that have incompatible interfaces;
		// - (only for adapter objects!) you need to use several existing subclasses, but impractical to adapt their interface by generating new subclasses of each.
		// class adapter uses inheritance.
		// object adapter uses composition.
		// Results for class adapter:
		// - Adaptee adapts to Target, entrusting particular class action Adaptee(don't works for subclasses)
		// - Adapter enables the adapter to replace some operations adaptable class Adaptee, since Adapter is nothing, as a subclass Adaptee;
		// - introduces only one new object. To get to the adapted class does not need any additional treatment at the sign.
		// Results for object adapter:
		// - It allows a single adapter Adapter works with many adaptable objects Adaptee, ie with itself and its subclasses Adaptee
		// - complicates the replacement class operations Adaptee. This will require to generate a subclass of Adaptee Adapter and make reference to this subclass and not on himself Adaptee.
		// Questions to discuss.
		// - the amount of work on adaptation.
		// - Replacement adapters.
		// - Use double-sided adapters to ensure transparency.
		// Realization:
		// - adapter class implementation in C ++.(private inheritance to adapter and public to target)
		// - Replacement adapters.
		// - parameterized adapters.

		// classes
		class Shape
		{
		public:
			Shape(){}
			virtual void boundingBox(){}
			virtual void createManipulator(){}
		};

		class TextView
		{
		public:
			TextView(){}
			void getOrigin(){}
			void getExtent(){}
			virtual bool isEmpty(){ return false; }
		};

		class TextShape : public Shape, private TextView
		{
		public:
			TextShape(){};

			void boundingBox() override;
			void createManipulator() override;
			bool isEmpty() override;
		};

		// objects
		class TextShape1 : public Shape
		{
		public:
			TextShape1(TextView* tv)
				:mTv(tv)
			{
			}

			void boundingBox() override;
			void createManipulator() override;
			virtual bool isEmpty();

		private:
			TextView* mTv;
		};
		// for objects it also works with subclasses.
		// related patterns: bridge, decorator, proxy.

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
		class WindowImpl;

		class Window
		{
		public:
			Window();

			virtual void draw();
			virtual void open();

			virtual void setOrigin();

		protected:
			WindowImpl* getWindowImpl();

		private:
			WindowImpl* impl;
		};

		class WindowImpl
		{
		public:
			virtual void top() = 0;
		};
		// we also can get windowimpl from widget factory, this factory creates all system-dependent objects.

		// Related:
		// - abstract factory, adapter.
		// Customers should be able to create a window, not being tied to a particular implementation.

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
		// - iterator

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

		// Facade.
		class CodeGenerator;
		class ProgramNodeBuilder;
		class Parser;
		class Scanner;
		class ByteCodeStream;

		class Compiler
		{
		public:
			Compiler();

			void compile(std::istream&, ByteCodeStream&);
		private:
			/*CodeGenerator* mCodeGenerator;
			ProgramNodeBuilder* mProgramNodeBuilder;
			Parser* mParser;
			Scanner* mScanner;*/
		};

		class Stream
		{

		};

		class ByteCodeStream : public Stream
		{

		};

		class StatementNode;
		class ExpressionNode;

		// Visitor example
		class CodeGenerator
		{
		public:
			virtual void visit(StatementNode*);
			virtual void visit(ExpressionNode*);

		protected:
			CodeGenerator(ByteCodeStream&);

		private:
			ByteCodeStream& mOutput;
		};

		class StackMachineCodeGenerator : public CodeGenerator
		{

		};

		class RISCCodeGenerator : public CodeGenerator
		{
		public:
			RISCCodeGenerator(ByteCodeStream&);
		};

		class ProgramNode;

		// Builder example
		class ProgramNodeBuilder
		{
		public:
			ProgramNodeBuilder();
			virtual ProgramNode* newVariable(const std::string& variableName) const;
			virtual ProgramNode* newAssignment(ProgramNode* variable, ProgramNode* expression) const;
			virtual ProgramNode* newReturnStatement(ProgramNode* value) const;
			virtual ProgramNode* newCondition(ProgramNode* condition, ProgramNode* truePart, ProgramNode* falsePart) const;

			ProgramNode* getRootNode();
		private:
			ProgramNode* mProgramNode;
		};

		class Token;
		class Symbol;

		// Composition
		class ProgramNode
		{
		public:
			virtual void getSourcePosition(int& line, int& index);

			virtual void add(ProgramNode*);
			virtual void remove(ProgramNode*);

			virtual void traverse(CodeGenerator&);
		protected:
			ProgramNode();
		};

		class StatementNode : public ProgramNode
		{

		};

		class ExpressionNode : public ProgramNode
		{
		public:
			void traverse(CodeGenerator&) override;
		};

		class VariableNode : public ProgramNode
		{

		};

		class Parser
		{
		public:
			Parser();
			virtual ~Parser();

			virtual void parse(Scanner&, ProgramNodeBuilder&);
		};

		class Scanner
		{
		public:
			Scanner(std::istream&);
			virtual ~Scanner();

			virtual Token& scan();

		private:
			std::istream& mInputStream;
		};

		class Token
		{

		};

		class Symbol
		{

		};
		// Use when:
		// - You want to provide a simple interface to a complex subsystem.
		// - between clients and the implementation classes of abstraction there are many dependencies.
		// - you want to expand the subsystem into separate layers.
		// Results:
		// - isolates clients from subsystem components, thereby reducing the number of objects that clients have to deal with and simplifying the work with the subsystem;
		// - It allows ease connectivity between the subsystem and its clients.
		// - facade does not preclude applications direct access to the subsystem classes if necessary.
		// Realization.
		// - reduction in the degree of relatedness of the client subsystem.
		// - open and closed classes of subsystems.
		// Related patterns:
		// - abstract factory
		// - mediator
		// - singleton

		// Flyweight
		// Use when all below is:
		// - The application uses a large number of objects
		// - because of this overhead storage High
		// - most of the state of objects can be taken outside
		// - Many groups of objects can be replaced by relatively few shared objects as rendered structural condition
		// - application does not depend on the identity of the object. Because objects can be separated by opportunists, then check on the identity of return "Truth" for conceptually distinct objects.
		// Results:
		// - decrease in the total number of copies;
		// - reducing the amount of memory required to store the internal state;
		// - calculation rather than an external storage status (if this is true).
		// Realization:
		// - the imposition of an external condition.
		// - management of shared objects.

		class Font;
		class GlyphContext;
		class Glyph
		{
		public:
			virtual ~Glyph();
			virtual void Draw(Window*, GlyphContext&);
			virtual void SetFont(Font*, GlyphContext&);
			virtual Font* GetFont(GlyphContext&);
			virtual void First(GlyphContext&);
			virtual void Next(GlyphContext&);
			virtual bool IsDone(GlyphContext&);
			virtual Glyph* Current(GlyphContext&);
			virtual void Insert(Glyph*, GlyphContext&);
			virtual void Remove(GlyphContext&);
		protected:
			Glyph();
		};

		class Character : public Glyph
		{
		public:
			Character(char);
			virtual void Draw(Window*, GlyphContext&);
		private:
			char _charcode;
		};

		class BTree;

		class GlyphContext
		{
		public:
			GlyphContext();
			virtual ~GlyphContext();
			virtual void Next(int step = 1);
			virtual void Insert(int quantity = 1);
			virtual Font* GetFont();
			virtual void SetFont(Font*, int span = 1);
		private:
			int _index;
			BTree* _fonts;
		};

		const int NCHARCODES = 128;
		class GlyphFactory {
		public:
			GlyphFactory();
			virtual ~GlyphFactory();
			virtual Character* CreateCharacter(char);
			//virtual Row* CreateRow();
			//virtual Column* CreateColumn();
		private:
			Character* _character[NCHARCODES];
		};
		// Related patterns: composition, strategy.
		// practice with Flyweight!!!.

		// Proxy.
		// Surrogate.
		class DocumentEditor
		{

		};

		class Graphic
		{
		public:
			virtual ~Graphic();

			virtual void draw();
			virtual void getExtent();
			virtual void store();
			virtual void load();
		};

		class Image : public Graphic
		{
		public:
			void draw() override;
			void getExtent() override;
			void store() override;
			void load() override;
		private:
			// imageImp 
			// extent
		};

		class ImageProxy : public Graphic
		{
		public:
			void draw() override;
			void getExtent() override;
			void store() override;
			void load() override;
		private:
			// filename 
			// extent
			Image* image;
		};

		// Use when:
		// - Remote assistant provides a local representative instead object in another address space.
		// - virtual assistant creates a "heavy" objects on demand.
		// - Deputy protects controls access to the original object.
		// - smart pointers.
		// Results:
		// - Remote substituent may hide the fact that the object is in a different address space;
		// - virtual assistant can perform optimizations, such as creating an object on demand;
		// - Deputy protects and "smart" links allow additional tasks when accessing the object.
		// - copy on demand.
		// Realization:
		// - overload operator access to members in C++.
		// - proxy shouldn't always be known type of real object.
		// Related Patterns:
		// - adapter, decorator
		// !!! practice with proxy.

		// Discussion of structural patterns
		// Adapter and Bridge.
		// Composition, Decorator and Proxy.
	}

	namespace chapter5
	{
		void main();

		// Chain of Responsibility
		// we say that request has implicit receiver
		// Use when:
		// - there is more than one object that can process the request, and a real processor known in advance and must be found automatically;
		// - you want to send a request to one of several objects without specifying obviously, what it is;
		// - a set of objects that can process the request must be set dynamically.
		// Results:
		// - weakening of cohesion.
		// - more flexibility in the allocation of responsibilities between objects.
		// - receiving is not guaranteed.
		// Realization:
		// - implementation chain successors.
		// - Connect successors.
		// - the submission of requests.

		typedef int Topic;
		const Topic NO_HELP_TOPIC = -1;

		class HelpHandler
		{
		public:
			HelpHandler(HelpHandler* = nullptr, Topic = NO_HELP_TOPIC);
			virtual bool hasHelp();
			virtual void setHandler(HelpHandler*, Topic);
			virtual void handleHelp();

		private:
			HelpHandler* _successor;
			Topic _topic;
		};

		class MyWidget : public HelpHandler
		{
		protected:
			MyWidget(MyWidget* parent, Topic t = NO_HELP_TOPIC);
		private:
			MyWidget* _parent;
		};

		class MyButton :public MyWidget
		{
		public:
			MyButton(MyWidget* h, Topic t = NO_HELP_TOPIC);
			void handleHelp() override;
		};

		class MyDialog : public MyWidget
		{
		public:
			MyDialog(HelpHandler* h, Topic t = NO_HELP_TOPIC);
			void handleHelp() override;
		};

		class MyApplication : public HelpHandler
		{
		public:
			MyApplication(Topic t) :HelpHandler(0, t){}
			void handleHelp() override;
		};

		const Topic PRINT_TOPIC = 1;
		const Topic PAPER_ORIENTATION_TOPIC = 2;
		const Topic APPLICATIONTOPIC = 3;
		// Related patterns: Composite.

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
		class SimpleCommand :public Command
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

		// Interpreter
		// Use when:
		// - Use the pattern interpreter when there is a language for interpreting, proposals which can be represented as abstract syntax trees.
		// - grammar is simple.
		// - efficiency is not the main criterion.
		// Results.
		// - grammar is easy to modify and expand.
		// - simple implementation of grammar.
		// - complex grammar is difficult to maintain.
		// - adding new ways to interpret expressions.
		// Realization:
		// - creating an abstract syntax tree.
		// - the definition of operation Interpret.
		// separation of terminal symbols with the pattern trimmer.

		class Context;

		class BooleanExp
		{
		public:
			BooleanExp(){};
			virtual ~BooleanExp(){};
			virtual bool evaluate(Context&) = 0;
			virtual BooleanExp* replace(const std::string&, BooleanExp&) = 0;
			virtual BooleanExp* copy() const = 0;
		};

		class VariableExp;

		class Context
		{
		public:
			bool lookup(const std::string&) const
			{
				return true;
			}
			void assign(VariableExp*, bool)
			{

			}
		};

		class VariableExp:public BooleanExp
		{
		public:
			VariableExp(const std::string&);
			virtual ~VariableExp(){};
			bool evaluate(Context&) override;
			BooleanExp* replace(const std::string&, BooleanExp&) override;
			BooleanExp* copy() const override;
		private:
			std::string _name;
		};

		class AndExp : public BooleanExp
		{
		public:
			AndExp(BooleanExp*, BooleanExp*);
			virtual ~AndExp(){};
			bool evaluate(Context&) override;
			BooleanExp* replace(const std::string&, BooleanExp&) override;
			BooleanExp* copy() const override;
		private:
			BooleanExp* _operandl;
			BooleanExp* _operand2;
		};

		// Related patterns:
		// - composition, trimmer, iterator, visitor.

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
		
		// Mediator.
		// Use when:
		// - There are objects, communications between them are complex and clearly defined.
		// - an object can not be reused because it communicates with many other objects.
		// - behavior, distributed between several classes should resist the setting up without generating a plurality of subclasses.
		// Results:
		// - reduces the number of generated subclasses.
		// - eliminates the coupling between colleagues.
		// - facilitates communication protocols objects.
		// - It abstracts the way to cooperation projects.
		// - centralizes management.
		// Realization.
		// - deliverance from the abstract class Mediator.
		// - the exchange of information between colleagues and intermediaries.

		class Widget1;

		class DialogDirector
		{
		public:
			virtual ~DialogDirector();

			virtual void showDialog();
			virtual void widgetChanged(Widget1*) = 0;

		protected:
			DialogDirector();
			virtual void createWidets() = 0;
		};

		class Widget1
		{
		public:
			Widget1(DialogDirector*);
			virtual void changed();

			virtual void handleMouse();

		private:
			DialogDirector* _director;
		};

		class ListBox :public Widget1
		{
		public:
			ListBox(DialogDirector*);

			virtual const std::string& getSelection();
			virtual void setList(const std::list<std::string>& items);
			void handleMouse() override;
		};

		class EntryField : public Widget1
		{
		public:
			EntryField(DialogDirector*);
			virtual void setText(const std::string& text);
			virtual const std::string& getText();
			void handleMouse() override;
		};

		class Button :public Widget1
		{
		public:
			Button(DialogDirector*);
			virtual void setText(const std::string& text);
			void handleMouse() override;
		};

		class FontDialogDirector :public DialogDirector
		{
		public:
			FontDialogDirector();
			virtual ~FontDialogDirector();

			void widgetChanged(Widget1*) override;

		protected:
			void createWidets() override;

		private:
			Button* _ok;
			Button* _cancel;
			ListBox* _fontList;
			EntryField* _fontName;
		};

		// Visitor.
		// Use when:
		// - the structure also contains objects of many classes with different interfaces and you want to perform operations on them, depending on the specific classes;
		// - on objects that are part of the structure, it is necessary to perform a variety, unrelated operation and you do not want to "clutter up" classes such operations.
		// - classes that establish the structure of objects rarely change, but new operations on this structure are added frequently.
		// Results:
		// - simplifies the addition of new operations.
		// - It combines related operations and cuts those that do not concern them.
		// - adding new classes ConcreteElement difficult.
		// - visiting different class hierarchies.
		// - accumulation state.
		// - violation of encapsulation.
		// Realization:
		// - double dispatch.
		// - What part is responsible for bypassing the structure.
		// Related Patterns:
		// - facade.
		// - observer.

		// Memento(Token).
		// Use when:
		// - to save a snapshot of an object (or part thereof), subsequently to the object can be reconstructed in the same state;
		// - direct receipt of this condition reveals implementation details and breaks encapsulation facility.
		// Results:
		// - preservation of boundaries encapsulation.
		// - simplification of the structure of the host.
		// - significant costs when using custodians.
		// - the definition of "narrow" and "broad" interfaces.
		// - the hidden charge for the content of the keeper.
		// Realization:
		// - language support.
		class State;
		class Memento;

		class Originator
		{
		public:
			Memento* createMemento();
			void setMemento(const Memento*);
		private:
			State* _state;
		};

		class Memento
		{
		public:
			virtual ~Memento();
		private:
			friend class Originator;
			Memento();

			void setState(State*);
			State* getState();

		private:
			State* _state;
		};
		// - preservation of the increment of change.

		class Graphic;
		class Point;
		class ConstraintSolverMemento;

		class MoveCommand
		{
		public:
			MoveCommand(Graphic* target, const Point& delta);
			void execute();
			void unExecute();

		private:
			ConstraintSolverMemento * _state;
			Point* _delta;
			Graphic* _target;
		};

		class ConstraintSolver
		{
		public:
			static ConstraintSolver* Instance();
			void solve();

			void addCostraint(Graphic* startConnection, Graphic* endConnection);
			void removeCostraint(Graphic* startConnection, Graphic* endConnection);

			ConstraintSolverMemento* createMemento();
			void setMemento(ConstraintSolverMemento*);

		private:

		};

		class ConstraintSolverMemento
		{
		public:
			virtual ~ConstraintSolverMemento();
		private:
			friend class ConstraintSolver;
			ConstraintSolverMemento();
		};
		// Related Patterns:
		// Commnad, Iterator.

		// from previous chapter
		typedef int Watt;
		typedef int Currency;
		class Equipment;
		typedef std::list<Equipment*> ContainerType;
		typedef ContainerType::iterator ContainerTypeIterator;

		class EquipmentVisitor;

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

			virtual void accept(EquipmentVisitor*);

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

			void accept(EquipmentVisitor*) override;
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

			void accept(EquipmentVisitor*) override;
		};

		class EquipmentVisitor
		{
		public:
			virtual ~EquipmentVisitor(){};
			virtual void visitFloppyDisk(FloppyDisk*){};
			virtual void visitChassis(Chassis*){};
		protected:
			EquipmentVisitor(){};
		};

		// Related patterns: composite, interpreter.

		// State.
		class TCPState;

		class TCPConnection
		{
		public:
			void open();
			void close();
			void acknowledge();
		private:
			TCPState* _state;
		};

		class TCPState
		{
		public:
			virtual void open();
			virtual void close();
			virtual void acknowledge();
		};

		class TCPEstablished :public TCPState
		{
		public:
			void open() override;
			void close() override;
			void acknowledge() override;
		};
		// Use when:
		// - when the behavior of an object depends on its condition and needs change over lead time;
		// - when operations occur in the code consisting of many conditional branches operators.
		// Results:
		// - localizes state-dependent behavior, and divides it into parts corresponding corresponding states.
		// - It is making clear transitions between states.
		// - state objects can be separated.
		// Realization:
		// - what defines the transitions between states.
		// - tabular alternative.
		// - the creation and destruction of objects of the state.
		// - the use of dynamic inheritance.
		// Related Patterns:
		// - trimmer.
		// - state.

		// Template Method
		// Use when:
		// - once to use the invariant part of the algorithm, leaving implementation to the discretion of the changing behavior of subclasses;
		// - when you need to isolate and localize in the same class behavior, general all subclasses to avoid duplicating code.
		// - to control subclasses extensions.
		// Realization:
		// - use of access control in C++.
		// - reducing the number of basic operations.
		// - naming convention.
		// Related patterns: template method, strategy.

		// Discussion of the behavior patterns
		// Encapsulation variations
		// - Generally, the patterns of behavior determined abstract class with which the object is described by encapsulating
		// - Objects as arguments.
		// - Should the exchange of information to be encapsulated or distributed.
		// - Separation of senders and recipients.
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