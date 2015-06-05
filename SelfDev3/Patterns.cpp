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
		chapter5::main();
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

		// Rectangle
		int Rectangle::area()
		{
			return mWidth * mHeight;
		}
		// Window
		Window::Window(Rectangle* r)
			:mR(r)
		{

		}

		int Window::area()
		{
			return mR->area();
		}

	}

	namespace chapter2
	{
		void main()
		{
			Window w;

			// Abstract Factory
			GUIFactory* factory = new GUIFactory;
			Button* button = factory->createButton();
			delete button;
			delete factory;

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

			// Visitor
			// SpellingChecker sc;

			// Iterator
			Glyph* g = new Glyph;
			Iterator<Glyph>* i = g->createIterator();
			for (i->first(); !i->isDone(); i->next())
			{
				Glyph* child = i->getCurrent();
				// child->checkMe(sc);
			}
		}

		// Abstract factory
		ScrollBar* GUIFactory::createScrollBar()
		{
			return new ScrollBar;
		}

		Button* GUIFactory::createButton()
		{
			return new Button;
		}

		Menu* GUIFactory::createMenu()
		{
			return new Menu;
		}

		void ScrollBar::ScrollTo(int)
		{

		}

		void Button::press()
		{

		}

		void Menu::popup()
		{

		}

		//*** Composite
		// Window
		void Window::drawRect(int x0, int x1, int y0, int y1)
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
		Glyph::~Glyph()
		{

		}

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

		void Character::checkMe(SpellingChecker& sc)
		{
			sc.checkCharacter(this);
		}

		// Rectangle
		void Rectangle::draw(Window* w)
		{
			w->drawRect(mX0, mX1, mY0, mY1);
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

		void Row::checkMe(SpellingChecker& sc)
		{
			sc.checkRow(this);
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

		void ApplicationWindow::drawContents()
		{

		}

		// MenuItem
		void MenuItem::clicked()
		{
			mCommand->execute();
		}
	}

	namespace chapter3
	{
		void main()
		{
			// It is Client
			MazeGame game;
			EnchantedMazeFactory factory;
			game.CreateMaze(factory);

			// Builder
			Maze* maze;
			MazeGame game1;
			StandardMazeBuilder builder;
			game1.CreateMaze(builder);
			maze = builder.getMaze();

			// Prototype
			//MazeGame game2;
			//MazePrototypeFactory simpleMazeFactory(new Maze, new Wall, new Room(0), new Door);
			//Maze* maze2 = game2.CreateMaze(simpleMazeFactory);
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

		Maze* MazeGame::CreateMaze(MazeBuilder& builder)
		{
			builder.buildMaze();
			builder.buildRoom(1);
			builder.buildRoom(2);
			builder.buildDoor(1, 2);

			return builder.getMaze();
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

		// Builder
		void RTFReader::parseRTF()
		{
			builder->convertCharacter();
		}

		// Factory Method
		Maze* MazeGame::makeMaze()
		{
			Maze* aMaze = MakeMaze();
			Room* rl = MakeRoom(1);
			Room* r2 = MakeRoom(2);
			Door* theDoor = MakeDoor(rl, r2);
			aMaze->AddRoom(rl);
			aMaze->AddRoom(r2);
			rl->setSide(North, MakeWall());
			rl->setSide(East, theDoor);
			rl->setSide(South, MakeWall());
			rl->setSide(West, MakeWall());
			r2->setSide(North, MakeWall());
			r2->setSide(East, MakeWall());
			r2->setSide(South, MakeWall());
			r2->setSide(West, theDoor);
			return aMaze;
		}

		// Singleton
		MazeFactorySingleton* MazeFactorySingleton::instance = nullptr;

		MazeFactorySingleton* MazeFactorySingleton::Instance()
		{
			if (instance == nullptr)
			{
				instance = new MazeFactorySingleton;
			}
			return instance;
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

		// Adapter for classes
		void TextShape::boundingBox()
		{
			getOrigin();
			getExtent();
		}

		void TextShape1::createManipulator()
		{
			// return new Manipulator;
		}

		bool TextShape1::isEmpty()
		{
			return mTv->isEmpty();
		}

		// Adapter for objects
		void TextShape1::boundingBox()
		{
			mTv->getOrigin();
			mTv->getExtent();
		}

		void TextShape::createManipulator()
		{
			// return new Manipulator;
		}

		bool TextShape::isEmpty()
		{
			return TextView::isEmpty();
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

		// Bridge
		void Window::open()
		{
			impl->top();
		}

		// Decorator.

		// Facade.
		void Compiler::compile(std::istream& input, ByteCodeStream& output)
		{
			//Scanner scanner(input);
			//ProgramNodeBuilder builder;
			//Parser parser;

			//parser.parse(scanner, builder);

			//RISCCodeGenerator generator(output);
			//ProgramNode* parseTree = builder.getRootNode();
			//parseTree->traverse(generator);
		}

		void ExpressionNode::traverse(CodeGenerator& eg)
		{
			eg.visit(this);
			//ListIterator<ProgramNode*> i(_children);
			//for (i.First(); !i.IsDone(); i.NextO) {
			//	i.Currentltem()->Traverse(eg);
			//}
		}

		// Proxy
		void ImageProxy::draw()
		{
			if (image == nullptr)
			{
				// image = load(filename);
			}
			image->draw();
		}

		void ImageProxy::getExtent()
		{
			if (image == nullptr)
			{
				//return extent;
			}
			else
			{
				return image->getExtent();
			}
		}
	}

	namespace chapter5
	{
		void main()
		{
			// Chain of Responsibility

			MyApplication* application = new MyApplication(APPLICATIONTOPIC);
			MyDialog* dialog = new MyDialog(application, PRINT_TOPIC);
			MyButton* button = new MyButton(dialog, PAPER_ORIENTATION_TOPIC);

			button->handleHelp();

			// Commnad
			//MyClass receiver;
			//Command* c = new SimpleCommand<MyClass>(receiver, &MyClass::action);
			// c->execute;

			// Interpreter

			// Observer
			//ClockTimer ct;
			//DigitalClock dc(&ct);
			//ct.start();
			//this_thread::sleep_for(chrono::seconds(10));
			//ct.stop();

			// Strategy
//			Composition* quick = new Composition(new SimpleCompositor);
//			Composition* slick = new Composition(new TeXCompositor);
//			Composition* iconic = new Composition(new ArrayCompositor(100));

			// Iterator
			//List <Employee*>* employees;
			//ListIterator<Employee*> forward(employees);
			//printEmployees(forward);
			// we can also use backward iterators.

			//AbstractList<Employee*>* employees;
			//Iterator<Employee*>* iterator = employees->CreateIterator();
			//printEmployees(*iterator);
			//delete iterator;

			//AbstractList<Employee*>* employees;
			//IteraratorPtr<Employee*> iterator(employees->CreateIterator());
			//printEmployees(*iterator);
		}

		// Chain of Responsibility
		HelpHandler::HelpHandler(HelpHandler* h, Topic t)
			:_successor(h),
			_topic(t)
		{
		}

		bool HelpHandler::hasHelp()
		{
			return _topic != NO_HELP_TOPIC;
		}

		void HelpHandler::handleHelp()
		{
			if (_successor != nullptr)
				_successor->handleHelp();
		}

		void HelpHandler::setHandler(HelpHandler* h, Topic t)
		{
			_successor = h;
			_topic = t;
		}

		MyWidget::MyWidget(MyWidget* parent, Topic t)
			:HelpHandler(parent, t),
			_parent(parent)
		{

		}

		MyButton::MyButton(MyWidget* h, Topic t)
			:MyWidget(h, t)
		{
		}

		void MyButton::handleHelp()
		{
			if (hasHelp())
			{

			}
			else
				HelpHandler::handleHelp();
		}

		MyDialog::MyDialog(HelpHandler* h, Topic t)
			: MyWidget(nullptr)
		{
			setHandler(h, t);
		}

		void MyDialog::handleHelp()
		{
			if (hasHelp())
			{

			}
			else
			{
				HelpHandler::handleHelp();
			}
		}

		void MyApplication::handleHelp()
		{

		}

		// Command
		OpenCommand::OpenCommand(Application* app)
			:mApplication(app)
		{

		}

		void OpenCommand::execute()
		{
			string name = askUser();
			if (name.empty() == false)
			{
				Document* document = new Document(name);
				mApplication->addDocument(document);
				document->open();
			}
		}

		const std::string& OpenCommand::askUser()
		{
			return mResponse;
		}

		// PasteCommand
		PasteCommand::PasteCommand(Document* document)
			:mDocument(document)
		{

		}

		void PasteCommand::execute()
		{
			mDocument->paste();
		}

		// Interpreter
		VariableExp::VariableExp(const std::string& name)
			:_name(name)
		{

		}

		bool VariableExp::evaluate(Context& c)
		{
			return c.lookup(_name);
		}

		BooleanExp* VariableExp::copy() const
		{
			return new VariableExp(_name);
		}

		BooleanExp* VariableExp::replace(const std::string& name, BooleanExp& exp)
		{
			if (!_name.empty())
				return exp.copy();
			else
				return new VariableExp(_name);
		}

		AndExp::AndExp(BooleanExp* opl, BooleanExp* op2)
		{
			_operandl = opl;
			_operand2 = op2;
		}

		bool AndExp::evaluate(Context& aContext)
		{
			return
				_operandl->evaluate(aContext) &&
				_operand2->evaluate(aContext);
		}

		BooleanExp* AndExp::copy() const
		{
			return
				new AndExp(_operandl->copy(), _operand2->copy());
		}
		BooleanExp* AndExp::replace(const std::string& name, BooleanExp& exp)
		{
			return
				new AndExp(
				_operandl->replace(name, exp),
				_operand2->replace(name, exp)
				);
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

		// Iterator
		void printEmployees(Iterator<Employee*>& i)
		{
			for (i.first(); !i.isDone(); i.next())
				i.current()->print();
		}
		
		// CompositeEquipment
		Currency CompositeEquipment::netPrice()
		{
			Currency total = 0;
			for (auto& item : mEquipment)
				total += item->netPrice();
			return total;
		}

		void FloppyDisk::accept(EquipmentVisitor* visitor)
		{
			//			visitor->visitFloppyDisk(this);
		}

		// Mediator
		void Widget1::changed()
		{
			_director->widgetChanged(this);
		}

		void Button::handleMouse()
		{
			changed();
		}

		void FontDialogDirector::createWidets()
		{
			//_ok = new Button(this);
			//_cancel = new Button(this);
			//_fontList = new ListBox(this);
			//_fontName = new EntryField(this);
		}

		void FontDialogDirector::widgetChanged(Widget1* theChangedWidget)
		{
			if (theChangedWidget == _fontList)
				_fontName->setText(_fontList->getSelection());
			else if (theChangedWidget == _ok)
			{
			}
			else if (theChangedWidget == _cancel)
			{
			}
		}

		// Memento.
		void MoveCommand::execute()
		{
			//ConstraintSolver * solver = ConstraintSolver::Instance();
			//_state = solver->createMemento();
			////_target->move(_delta);
			//solver->solve();
		}

		void MoveCommand::unExecute()
		{
			//ConstraintSolver* solver = ConstraintSolver::Instance();
			//_target->move(-_delta);
			//solver->setMemento(_state);
			//solver->solve();
		}

		// State
		void TCPConnection::open()
		{
			_state->open();
		}

		void TCPConnection::close()
		{

		}

		void TCPConnection::acknowledge()
		{

		}

		// Template Method

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