#pragma once

#include<iostream>
#include<string>
#include<list>
#include<map>

namespace system_of_patterns
{
	void main();
	// Architectural patterns are the highest-level patterns. They are intended to provide the skeleton of an overall system architecture.

	// Patterns.
	namespace chapter1
	{
		void main();

		// Model-View-Controller.
		// - Changes to the user interface should be easy, and possible at runtime.
		// - Adapting or porting the user interface should not impact code in the functional core of the application.
		// three areas : processing, output and input :
		// - The model component encapsulates core data and functionality.
		// - View components display information to the user.
		// - Each view has an associated controller component. The user interacts with the system solely via controllers.

		class Observer
		{
		public:
			virtual void update() = 0;
		};

		class Model
		{
		public:
			void attach(Observer* o);
			void detach(Observer* o);
			void notify();
		private:
			std::list<Observer*> _observers;
		};

		class Controller;

		class View : public Observer
		{
		public:
			void initialize(Model* m);
			Controller* makeController();

			void activate();
			void display();

			void update() override;

		private:
			Model* myModel;
			Controller* myController;
		};

		class Controller : public Observer
		{
		public:
			void initialize(Model*, View*);
			void handleEvent();

			void update() override;

		private:
			Model* myModel;
			View* myView;
		};
		// interactive system

		// Context: a situation giving rise to a problem.
		// Problem : the recurring problem arising in that context.
		// Solution : a proven resolution of the problem.

		// Groups of patterns:
		// - Architectural patterns
		// - Design patterns
		// - Idioms
	}

	// Architectural Patterns
	namespace chapter2
	{
		void main();
		// 4 categories:
		// - From Mud to Structure
		// - Distributed Systems
		// - Interactive Systems.
		// - Adaptable Systems.

		// 2.2. From Mud to Structure
		// - The Layers pattern helps to structure applications that can be decomposed into groups of subtasks in which each group of subtasks is at a particular level of abstraction.
		// - The Pipes and Filters pattern provides a structure for systems that process a stream of data.Each processing step is encapsulated in a filter component.Data is passed through pipes between adjacent filters.Recombining filters allows you to build families of related systems.
		// - The Blackboard pattern pattern is useful for problems for which no deterministic solution strategies are known. In Blackboard several specialized subsystems assemble their knowledge to build a possibly partial or approximate solution.

		// LAYERS.
		// EXAMPLE:
		// OSI 7-layer model.
		// - Application : Provides miscellaneous protocols for common activities
		// - Presentation : structures information and attaches semantics
		// - Session : Provides dialog control and synchronization facilities
		// - Transport : Breaks messages into packets and guarantees delivery
		// - Network : Selects a route from sender to receiver
		// - Data Link : Detects and corrects errors in bit sequences
		// - Physical : Transmits bits: velocity, bit - code, connection, etc
		// the reuse of individual layers in different contexts:
		// TCP for example can be used 'as is' by diverse distributed applications such as telnet or ftp
		// CONTEXT: A large system that requires decomposition.
		// PROBLEM:
		// forces:
		// - Late source code changes should not ripple through the system.
		// - Interfaces should be stable. and may even be prescribed by a standards body.
		// - Parts of the system should be exchangeable.
		// - It may be necessary to build other systems at a later date with the same low - level issues as the system you are currently designing
		// - Similar responsibilities should be grouped to help understandability and maintainability
		// - There is no 'standard' component granularity.
		// - Complex components need further decomposition.
		// - Crossing component boundaries may impede performance
		// - The system will be built by a team of programmers.
		// SOLUTION: simple layers.
		// DYNAMICS:
		// top -> down and bottom -> up scenarios are possible.
		// IMPLEMENTATION:
		// 1. Define the abstraction criterion for grouping tasks into layers(chess game for example)
		// layers from bottom to top:
		// - Elementary units of the game, such as a bishop
		// - Basic moves, such as castling
		// - Medium-term tactics, such as the Sicilian defense
		// - Overall game strategies.
		// other sw architecture example:
		// - User-visible elements.
		// - Specific application modules
		// - Common services level
		// - Operating system interface level
		// - Operating system (being a layered system itself, or structured according to the Microkernel pattern)
		// - Hardware.
		// 2. Determine the number of abstraction levels according to your abstraction criterion.
		// 3. Determine the number of abstraction levels according to your abstraction criterion.
		// 4. Specih the services.
		// 5. Refine the layering. 
		// 6. Specify an interface for each layer.
		// design a flat interface that offers all Layer J's services, and perhaps encapsulate this interface in a Facade object.
		// 7. Structure individual layers.
		// For example, you can use the Bridge pattern to support multiple implementations of services provided by a layer.
		// The Strategy pattern can	support the dynamic exchange of algorithms used by a layer.
		// 8. Specth the communication between adjacent layers.
		// The most often used mechanism for inter - layer communication is the push model.
		// The reverse is known as the pull model.
		// 9. Decouple adjacent layers.
		// During start-up the higher layer tells the lower layer what functions to call when specific events occur.
		 
		class L1Provider
		{
		public:
			virtual void L1Service() = 0;
		};

		class L2Provider
		{
		public:
			virtual void L2Service() = 0;
			void setLowerLayer(L1Provider* l1)
			{
				level1 = l1;
			}
		protected:
			L1Provider* level1;
		};

		class L3Provider
		{
		public:
			virtual void L3Service() = 0;
			void setLowerLayer(L2Provider * l2)
			{
				level2 = l2;
			}
		protected:
			L2Provider *level2;
		};

		class DataLink : public L1Provider
		{
		public:
			void L1Service() override
			{
				std::cout << "L1Service doing it's job\n";
			}
		};

		class Transport : public L2Provider
		{
		public:
			void L2Service() override
			{
				std::cout << "L2Service starting its job\n";
				level1->L1Service();
				std::cout << "L2Service finishing its job\n";
			}
		};

		class Session : public L3Provider
		{
		public:
			void L3Service() override
			{
				std::cout << "L3Service starting its job\n";
				level2->L2Service();
				std::cout << "L3Service finishing its job\n";
			}
		};
		
		// 10. Design an error-handling strategy.
		// EXAMPLE: communication protocol TCP/IP.
		// - FTP
		// - TCP
		// - IP
		// - Ethernet
		// VARIANTS
		// - Relaxed Layered System.
		// The gain of flexibility and performance in a Relaxed Layered System is paid for by a loss of maintainability.
		// - Layering Through Inheritance.
		// KNOWN USES:
		// - virtual machines.
		// - APIs.
		// - Information Systems: 2 - layer interface. The bottom layer is a database. Many applications work concurrently on top of this database to fulfill different tasks.
		// Presentation
		// Application logic
		// Domain layer
		// Database
		// - Windows NT
		// System services
		// Resource management layer
		// Kernel
		// Hardware Abstraction Layer
		// Hardware
		// CONSEQUENCES
		// benefits:
		// - Reuse of layers.
		// If an individual layer embodies a well-defined abstraction and has a well - defined and documented interface, the layer can be reused in multiple contexts.
		// - Support for standardization.
		// - Dependencies are kept local.
		// - Exchangeability.
		// You can even replace an old implementation with an implementation with a different interface by using the Adapter pattern for interface adaptation.
		// The other extreme is dynamic exchange, which you can achieve by using the Bridge pattern.
		//	liabilities:
		// - Cascades of changing behavior.
		// - Lower efficiency.
		// - Unnecessary work.
		// - Difiulty of establishing the correct granularity of layers.
		// - Composite Message.

		// PIPES AND FILTERS.
		// The Pipes and Filters architectural pattern provides a structure for systems that process a stream of data.
		// CONTEXT:
		// Processing data streams.
		// PROBLEM:
		// forces:
		// - Future system enhancements should be possible by exchanging processing steps or by recombination of steps, even by users.
		// - Small processing steps are easier to reuse in different contexts than large components.
		// - Non-adjacent processing steps do not share information.
		// - Different sources of input data exist, such as a network connection or a hardware sensor providing temperature readings, for example.
		// - It should be possible to present or store final results in various	ways.
		// - Explicit storage of intermediate results for further processing in files clutters directories and is error - prone, if done by users.
		// - You may not want to rule out multi-processing the steps, for example running them in parallel or quasi - parallel.
		// SOLUTION:
		// processing steps - filters are connected by pipes.
		// STRUCTURE:
		// The activity of a filter can be triggered by several events:
		// - The subsequent pipeline element pulls output data from the filter
		// - The previous pipeline element pushes new input data to the filter
		// - Most commonly, the filter is active in a loop, pulling its input from and pushing its output down the pipeline
		// An active filter starts processing on its own as a separate program or thread.
		// DYNAMICS:
		// filters can connect to other filters in some variants.
		// Most common variant:
		// All filters actively pull, compute. and push data in a loop. Each filter therefore runs in its own thread of control, for example as a separate process.
		// IMPLEMENTATION:
		// 1. Divide the system's task into a sequence of processing stages.
		// 2. Define the data format to be passed along each pipe.
		// 3. Decide how to implement each pipe connection.
		// 4. Design and implement the filters.
		// As a rule of thumb, a filter should do one thing well.
		// 5. Design the error handling.
		// 6. Set up the processing pipeline.
		// EXAMPLE RESOLVED.
		// VARIANTS.
		// - Tee and join pipeline systems.
		// KNOWN USES.
		// - UNIX.
		// - CMS Pipelines.
		// - LASSPTools
		// CONSEQUENCES:
		// benefits:
		// - No intermediate files necessary, but possible.
		// - Flexibility by filter exchange.
		// - Flexibility by recombination.
		// - Reuse of filter components.
		// - Rapid prototyping of piplines.
		// - Egiciemy by parallel processing.
		// liabilities:
		// - Sharing state information is expensive or inflxible.
		// - Efficiency gain by parallel processing is often an illusion.
		// 1. The cost for transferring data between filters may be relatively high compared to the cost of the computation carried out by a single filter.This is especially true for small filter components or pipelines using network connections.
		// 2. Some filters consume all their input before producing any output, either because the task, such as sorting, requires it or because the filter is badly coded, for example by not using incremental processing  when the application allows it.
		// 3. Context-switching between threads or processes is generally an expensive operation on a single - processor machine.
		// 4. Synchronization of filters via pipes may stop and start filters often, especially when a pipe has only a small buffer.
		// - Data transformation overhead.
		// - Error handling.
		// SEE ALSO:
		// The Layers pattern.
		// CREDITS:
		// Unix.

// BLACKBOARD.
// The Blackboard architectural pattern is useful for problems for which no determlnlstic solution strategies are known.In Blackboard several specialized subsystems assemble their knowledge to bulld a possibly partial or approximate solution.
// EXAMPLE.
// speech recognition.
// CONTEXT
// An immature domain in which no closed approach to a solution is known or feasible.
// Problem:
// Vision, image recognition, speech recognition and surveillance are examples of domains in which such problems occur.
// forces:
// - A complete search of the solution space is not feasible in a reasonable time.
// - Since the domain is immature, you may need to experiment with different algorithms for the same subtask.
// - There are different algorithms that solve partial problems.
// - Input, as well as intermediate and final results, have different representations, and the algorithms are implemented according to different paradigms.
// - An algorithm usually works on the results of other algorithms.
// - Uncertain data and approximate solutions are involved.
// - Employing disjoint algorithms incduces potential parallelism.
// SOLUTION.
// The idea behind the Blackboard architecture is a collection of independent programs that work cooperatively on a common data structure.
// opportunistic problem solving.
// STRUCTURE:
// - Divide your system into a component called blackboard, a collection of knowledge sources, and a control component.
// DYNAMICS:
// IMPLEMENTATION:
// 1. Define the problem:
// - Specify the domain of the problem and the general fields of knowledge necessary to find a solution.
// - Define the output of the system.
// - Detail how the user interacts with the system.
// 2. Define the solution spacefor the problem.
// perform following steps:
// - Specify exactly what constitutes a top-level solution.
// - List the different abstraction levels of solutions.
// - Organize solutions into one or more abstraction hierarchies.
// - Find subdivisions of complete solutions that can be worked on independently, for example words of a phrase or regions of a picture or area.
// 3. Divide the solution process into steps :
// - Define how solutions are transformed into higher-level solutions.
// - Describe how to predict hypotheses at the same abstraction level.
// - Detail how to verify predicted hypotheses by finding support for them in other levels.
// - Specify the kind of knowledge that can be used to exclude parts of the solution space.
// 4. Divide the knowledge into specialized knowledge sources with certain subtasks.
// 5. Define the vocabulary of the blackboard.
// 6. Specify the control ofthe system.
// - Classifying changes to the blackboard into two types.
// - Associating categories of blackboard changes with sets of possibly applicable knowledge sources.
// - Focusing of control.
// - Creating a queue in which knowledge sources classified as applicable wait for their execution.
// Here are some examples of heuristics that can be used by control strategies:
// - Prioritizing applicable knowledge sources.
// - Preferring low-level or high-level hypotheses.
// - Preferring hypotheses that cover large parts of the problem.
// - 'Island driving'. This strategy involves assuming that a particular hypothesis is part of an acceptable solution, and is considered as an 'island of certainty'.
// 7. Implement the knowledge sources.
// VARIANTS:
// - Production System.
// - Repository.
// KNOWN USES:
// 1) HEARSAY-2.
// The control component of HEARSAY-2 consists of the following:
// - The focusofcontrol database.
// - The scheduling queue.
// - The monitor.
// - The scheduler.
// 2) HASP / SIAP.
// 3) CRYSALIS.
// 4) TRICERO.
// 5) Generalizations.
// 6) SUS.
// EXAMPLE RESOLVED:
// CONSEQUENCES:
// - Experimentation.
// - Support for changeability and maintainability.
// - Reusable knowledge sources.
// - Support for fault tolerance and robustness.
// liabilities:
// - Difficulty of testing.
// - No good solution is guaranteed.
// - Diffculty of establishing a good control strategy.
// - Low Efficiency.
// - High development effort.
// - No support for parallelism.
// CREDITS:

// 2.3. Distributed Systems.
// There are two major trends in recent developments in hardware technology:
// - Computer systems with multiple CPUs are entering wen small offices.
// - Local area networks connecting hundreds of heterogeneous computers have become commonplace.
// Pluses:
// - Economics.
// - Performance and Scalability.
// - Inherent distribution
// - Relhbillty.
// three patterns related to distributed systems:
// - The Pipes and Filters pattern provides a structure for systems that process a stream of data.Each processing step is encapsulated in a filter component.Data is passed through pipes between adjacent filters.Recombining filters allows you to build families of related systems.
// - The Microkernel pattern (171) applies to software systems that must be able to adapt to changing system requirements.
// - The Broker pattern can be used to structure distributed software systems with decoupled components that interact by remote service invocations.
// three groups of developers who can benefit by using the Broker pattern:
// - Those working with an existing Broker system who are interested in understanding the architecture of such systems.
// - Those who want to build 'lean' versions of a Broker system, without all the bells and whistles of a full - blown OLE or CORBA.
// - Those who plan to implement a hlly-fledged Broker system, and therefore need an in - depth description of the Broker architecture.

// BROKER.
// The Broker architectural pattern can be used to structure distributed software systems with decoupled components that interact by remote service invocations.A broker component Is responslble for coordinating communication, such as forwarding requests.as well as for transmitting results and exceptions.
// EXAMPLE.
// city information system.
// CONTEXT.
// - Your environment is a distributed and possibly heterogeneous system with independent cooperating components.
// Problem.
// Building a complex software system as a set of decoupled and interoperating components, rather than as a monolithic application, results in greater flexibility, maintainability and changeability.
// An application that uses an object should only see the interface offered by the object.It should not need to know anything about the implementation details of an object, or about its physical location.
// forces:
// - Components should be able to access services provided by others through remote, location - transparent service invocations.
// - You need to exchange, add, or remove components at run-time.
// - The architecture should hide system- and implementation-specific details from the users of components and services.
// SOLUTION
// Introduce a broker component to achieve better decoupling of clients and servers.
// STRUCTURE
// The Broker architectural pattern comprises six types of participating components: clients.servers, brokers, bridges, client - side proxies and server - side proxies.
// These interfaces are made available either through an interface definition language(IDL).
// 2 kinds of servers:
// - Servers offering common services to many application domains.
// - Servers implementing specific functionality for a single application domain or task.
// - Clients are applications that access the services of at least one server.
// - A broker is a messenger that is responsible for the transmission of requests from clients to servers, as well as the transmission of responses and exceptions back to the client.
// - Client-side proxies represent a layer between clients and the broker.
// the proxies allow the hiding of implementation details from the clients such as:
// 1 The inter-process communication mechanism used for message transfers between clients and brokers.
// 2 The creation and deletion of memory blocks.
// 3 The marshaling of parameters and results.
// Sewer-side proxies are generally analogous to Client-side proxies. 
// - Bridges are optional components used for hiding implementation details when two brokers interoperate.
// The Client - Dispatcher - Server pattern(323) describes the important aspects of the direct variant of the Broker pattern
// DYNAMICS.
// IMPLEMENTATION
// 1. Define an object model, or use an existing model.
// 2. Decide whtch kind of component-interoperability the system should offer.
// For example, binary method tables are available in Microsoft Object Linking and Embedding(OLE)
// the IDL approach is more flexible in that an IDL mapping may be implemented for any programming language
// 3. Speccify the APIs the broker component providesfor collaborating with clients and servers.
// 4. Use proxy objects to hide implementation details from clients and servers.
// proxy objects responsibility:
// - Client-side proxies package procedure calls into messages and forward these messages to the local broker component.
// - Server-side proxies receive requests from the local broker and call the methods in the interface implementation of the corresponding server.
// If you follow the IDL approach for interoperability, proxy objects are automatically available, because they can be generated by an IDL compiler.If you use a binary approach, the creation and deletion of proxy objects can happen dynamically.
// 5. Design the broker component in parallel with steps 3 and 4.
// 5.1. Specify a detailed on-the-wire protocol for interacting with client-side proxies and server - side proxies.
// 5.2. A local broker must be available for every participating machine in the network.
// 5.3. When a client invokes a method of a server, the Broker system is responsible for returning all results and exceptions back to the original client
// 5.4. If the proxies (see step 4) do not provide mechanisms for marshaling and unmarshaling parameters and results, you must include that functionality in the broker component.
// 5.5. If your system supports asynchronous communication between clients and servers, you need to provide message buffers within the broker or within the proxies for the temporary storage of messages.
// 5.6. Include a directory service for associating local server identifiers with the physical location of the corresponding servers in the broker.
// if the underlying inter-process communication protocol is based on TCP / IP, you could use an Internet port number as the physical server location.
// 5.7. When your architecture requires system-unique identifiers to be generated dynamically during server registration, the broker must offer a name service for instantiating such names
// 5.8. If your system supports dynamic method invocation (see step 3), the broker needs some means for maintaining type information about existing servers.
// 5.9. Consider the case in which something fails. In a distributed system two levels of errors may occur :
// 1) A component such as a server may run into an error condition.
// 2) The communication between two independent processes may fail.
// 6. Develop IDL compilers.
// When many programming languages are in use, it is best to develop the compiler as afrarnework that allows the developer to add his own code generators.
// EXAMPLE RESOLVED.
// VARIANTS:
// - Dtrect Communication Broker System.
// - Message Passing Broker System.
// - Trader System.
// - Adapter Broker System.
// - Callback Broker System.
// KNOWN USES:
// - CORBA.
// - IBM SOM/DSOM.
// - Microsoft's OLE 2.x.
// - WWW
// - ATM-P
// CONSEQUENCES:
// benefits:
// - Location Transparency.
// - Changeability and extensibility of components.
// - Portability of a Broker system. Use Layers so you need to port only low-level system specific part.
// - Interoperability between dzflerent Broker systems.
// - Reusability.
// liabilities:
// - Restricted emiency.
// - Lower fault tolerance.
// The following aspect gives benefits as well as liabilities:
// Testing and Debugging:
// SEE ALSO:
// - The Forwarder-Receiver pattern encapsulates inter-process communication between two components.
// - The Proxy pattern.
// - The Client-DispatcherServer pattern is a lightweight version of the Direct Communication Broker variant.
// - The Mediator design pattern replaces a web of inter-object connections by a star configuration in which the central mediator component encapsulates collective behavior by defining a common interface for communicating with objects.

// 2.4 Interactive Systems
// the challenge is to keep the functional core independent of the user interface.
// 2 patterns for interactive systems:
// - The Model-View-Controller pattern (MVC) divides an interactive application into three components.
// - The Presentation-Abstraction-Control pattern (PAC) defines a structure for interactive software systems in the form of a hierarchy of cooperating agents.

// MODEL-VIEV-CONTROLLER.
// The model contains the core functionality and data.Views display information to the user. Controllers handle user input.
// CONTEXT:
// - Interactive applications with a flexible human-computer interface.
// PROBLEM:
// User interfaces are especially prone to change requests.
// forces:
// - The same information is presented differently in different windows, for example, in a bar or pie chart.
// - The display and behavior of the application must reflect data manipulations immediately.
// - Changes to the user interface should be easy, and even possible at run - time.
// - Supporting different 'look and feel' standards or porting the user interface should not affect code in the core of the application.
// SOLUTION:
// MVC divides an interactive application into the three areas : processing, output, and input.
// Publisher-Subscriber pattern.
// STRUCTURE:
// The model component contains the functional core of the application.
// class Model
// responsibility:
// - Provides functional core of the application.
// - Registers dependent views and controllers.
// - Notifies dependent components about data changes.
// collaborators:
// - View
// - Controller
// View components present information to the user.
// class View
// Responsibility:
// - Creates and initializes its associated controller.
// - Displays information to the user.
// - Implements the update procedure.
// - Retrieves data from the model.
// Collaborators:
// - Controller
// - Model
// The controller components accept user input as events.
// class Controller
// Responsibility:
// - Accepts user input as events.
// - Translates events to service requests for the model or display requests for the view.
// - Implements the update procedure, if required.
// Collaborators:
// - View
// - Model

class Observer
{
public:
	virtual void update() = 0;
};

class Model;
class Controller;

class Event
{

};

class View : public Observer
{
public:
	View(Model* m);
	virtual ~View();

	void update() override;

	virtual void initialize();
	virtual void draw();
	virtual Controller* makeController();

	Model * getModel();
	Controller* getController();

	virtual Controller* setController(Controller* c);

private:
	Model* _model;
	Controller* _controller;
};

class Controller : public Observer
{
public:
	Controller(View* v);
	virtual ~Controller();

	void update() override;

//	void initialize(Model* m, View* v);
	virtual void handleEvent(Event* e);

protected:
	Model* _model;
	View* _view;
};

class Model
{
public:
	void attach(Observer* o);
	void detach(Observer* o);

protected:
	void notify();

private:
	std::list<Observer*> _observers;
	Model* _model;
	Controller* _controller;
};
// DYNAMICS:
// several scenarios.
// IMPLEMENTATION:
// 1. Separate human-computer interactionfrom core functionality.
class VotesModel : public Model
{
public:
	VotesModel(const std::map<std::string, int>& votes);
	void clearVotes();
	void changeVote(const std::string& vote, int value);
private:
	std::map<std::string, int> _votes;
};
// 2. Implement the change-propagation mechanism.
// 3. Design and implement the views.
class BarChartView : public View
{
public:
	BarChartView(Model *m)
		: View(m)
	{}

	// shows data as BarChart
	void draw() override
	{}
};
// 4. Design and implement the controllers.
// For example, the controller may register its eventhandling procedure with the window system as a callback.
// 5. Design and implement the view-controller relationship.
class TableView;
class TableController : public Controller
{
public:
	TableController(TableView *tv);
	void handleEvent(Event *e) override;
};

class TableView : public View
{
public:
	TableView(Model *m);
	void draw() override;
	Controller* makeController() override;
};
// 6. Implement the set-up of MVC.
// 7. Dynamic view creation.
// Apply the View Handler design pattern
// 8. 'Pluggable controllers.
// 9. Infrastructure for hierarchical views and controllers.
// Apply the Composite pattern to create hierarchically composed views.
// If multiple views are active simultaneously Use the Chain of Responsibility pattern to manage this delegation of events.
// 10. Further decoupling from system dependencies.
// you can use Bridge to make it system independent.
// VARIANTS:
// Document - View.
// combine the responsibilities of the view and the controller from MVC in a single component.
// KNOWN USES:
// - Smalltalk
// - MFC
// - ET++

// CONSEQUENCES:
// benefits:
// - Multiple views of the same model.
// - Synchronized views.
// - 'Pluggable' views and controllers.
// - Exchangeability of 'look and feel'.
// - Framework potential.
// liabilities:
// - Increased complexity.
// - Potential for excessive number of updates.
// - Intimate connection between view and controller.
// - Close coupling of views and controllers to a model.
// apply the Command Processor pattern to resolve.
// - Inefficiency of data access in view.
// - Inevitability of change to view and controller when porting.
// - Difficulty of using MVC with modern user-interface tools.
// user interface tools provides lots of ways to show gui.
// SEE ALSO:
// - Presentation-Abstraction-Control.

// Presentation-Abstraction-Control

// practice with all patterns, learn something new if needed. !!!
	}
}
