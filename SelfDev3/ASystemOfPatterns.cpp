#include "ASystemOfPatterns.h"
#include "algorithm"

using namespace std;

namespace system_of_patterns
{
	void main()
	{
		chapter1::main();
		chapter2::main();
	}

	namespace chapter1
	{
		void main()
		{

		}
	}

	namespace chapter2
	{
		void main()
		{
			// Layers.
			DataLink datalink;
			Transport transport;
			Session session;

			transport.setLowerLayer(&datalink);
			session.setLowerLayer(&transport);

			session.L3Service();

			// MVC.
			map<string, int> data;
			data["red"] = 10;
			data["green"] = 20;
			data["blue"] = 30;

			VotesModel m(data);

			TableView* v1 = new TableView(&m);
			v1->initialize();
			BarChartView* v2 = new BarChartView(&m);
			v2->initialize();

			// delete v1->setController(new Controller(v1));
		}

		// MVC
		void Model::attach(Observer* o)
		{
			_observers.push_back(o);
		}

		void Model::detach(Observer* o)
		{
			_observers.remove(o);

		}

		void Model::notify()
		{
			for (auto& el : _observers)
				el->update();
		}

		View::View(Model* m)
			:_model(m), _controller(nullptr)
		{
			_model->attach(this);
		}

		View::~View()
		{
			_model->detach(this);
		}

		void View::update()
		{

		}

		void View::initialize()
		{
			_controller = makeController();
		}

		void View::draw()
		{

		}

		Controller* View::makeController()
		{
			return new Controller(this);
		}

		Model* View::getModel()
		{
			return _model;
		}

		Controller* View::getController()
		{
			return _controller;
		}

		Controller* View::setController(Controller* c)
		{
			Controller* old = _controller;
			_controller = c;
			return old;
		}

		Controller::Controller(View* v)
			:_view(v)
		{
			_model = _view->getModel();
			_model->attach(this);
		}

		Controller::~Controller()
		{
			_model->detach(this);
		}

		void Controller::update()
		{

		}

		//void Controller::initialize(Model* m, View* v)
		//{
		//	_model = m;
		//	_view = v;
		//}

		void Controller::handleEvent(Event* e)
		{

		}

		VotesModel::VotesModel(const std::map<std::string, int>& votes)
			:_votes(votes)
		{

		}

		void VotesModel::clearVotes()
		{
			_votes.clear();
			notify();
		}

		void VotesModel::changeVote(const std::string& vote, int value)
		{
			if (_votes.find(vote) == _votes.end())
				return;
			_votes[vote] = value;
			notify();
		}

		TableController::TableController(TableView *tv)
			:Controller(tv)
		{

		}

		void TableController::handleEvent(Event *e)
		{

		}

		TableView::TableView(Model *m)
			:View(m)
		{

		}

		void TableView::draw()
		{

		}

		Controller* TableView::makeController()
		{
			return new TableController(this);
		}
	}
}