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
// The Presentation - Abstraction - Control architectural pattern(PAC) defines a structure for interactive software systems in the form of a hierarchy of cooperating agents.
// EXAMPLE:
// CONTEXT:
// Development of an interactive application with the help of agents.
// PROBLEM:
// each agent is specialized for a specific task, and all agents together provide the system functionality.
// forces:
// - However, individual agents must effectively cooperate to provide the overall task of the application.
// - Interactive agents provide their own user interface, since their respective human - computer interactions often differ widely.
// - Systems evolve over time.
// Changes to individual agents, or the extension of the system with new agents, should not affect the whole system.
// SOLUTION:
// - Structure the interactive application as a tree-like hierarchy of PAC agents.There should be one top - level agent, several intermediatelevel agents, and even more bottom - level agents.
// each agent has 3 components: presentation, abstraction, and control.
// The agent's presentation component provides the visible behavior of the PAC agent.Its abstraction component maintains the data model that underlies the agent, and provides functionality that operates on this data.Its control component connects the presentation and abstraction components, and provides fimctionality that allows the agent to communicate with other PAC agents.
// - The top-level PAC agent provides the functional core of the system.
// - Bottom-level PAC agents represent self-contained semantic concepts
// - Intermediate-level PAC agents represent either combinations of, or relationships between, lower - level agents.
// STRUCTURE:
// The control component of the top-level PAC agent has three responsibilities:
// - It allows lower-level agents to make use of the services of the toplevel agents, mostly to access and manipulate the global data model.
// - It coordinates the hierarchy of PAC agents.
// - It maintains information about the interaction of the user with the system.
// Bottom-level PAC agents represent a specific semantic concept of the application domain.
// Intermediate-Level PAC agents can fulfill two different roles: composition and coordination.

// class: Top-level Agent
// Responsibility:
// - Provides the functional core of the system.
// - Controls the PAC hierarchy.
// Collaborators:
// Intermediate-level Agent
// - Bottom-level Agent

// class: Interm. -level Agent
// Responsibility:
// - Coordinates lowerlevel PAC agents.
// - Composes lowerlevel PAC agents to a single unit of higher abstraction.
// Collaborators:
// - Top-level Agent
// - Intermediatelevel Agent
// - Bottom-level Agent
// Responsibility:
// - Provides a speciflc view of the software or a system service, including its associated human - computer interaction.
// Collaborators:
// - Top-level Agent
// - Intermediate level Agent

// We keep the interfaces of PAC agents small by applying the Composite Message pattern.

// DYNAMICS:
// IMPLEMENTATION:
// 1. Define a model of the application.
// - Which services should the system provide ?
// - Which components can fulfill these services ?
// - What are the relationships between components ?
// - How do the components collaborate ?
// - What data do the components operate on ?
// - How will the user interact with the software ?
// 2. Define a general strategy for organizing the PAC hierarchy.
// rule of lowest common ancestor.
// consider is the depth of the hierarchy.
// 3. SpeciA the top-level PAC agent.
// 4. Spectfy the bottom-level PAC agents.
// 5. Speclh bottom-level PAC agents for system services.
// 6. Specify intermediate-level PAC agents to compose lower-level PAC agents.
// 7. Specih intermediate-level PAC agents to coordinate lower-level PAC agents.
// 8. Separate core functionality from human-computer interaction.
// You can provide a unified interface to the abstraction and presentation components of a PAC agent by applying the Facade pattern.
// You can apply the Command Processor pattern to further organize the presentation component.
// The control component is implemented  as an Adapter.
// 9. Rovide the external interface.
// the control component is a mediator you may use the Mediator pattern.
// One way of implementing communication with other agents is to apply the Composite Message pattern.
// Publisher-Subscriber pattern.
// 10. Link the hierarchy together.
// VARIANTS:
// - PAC agents as actiue objects.
// Design patterns like Active Object and Half - Sync / Half - Async can help you implement such an architecture.
// - PAC agents as processes.
// use proxies to locally represent remote PAC agents.
// - Use the Forwarder-Receiver pattern or the Client-Dispatcher-Server pattern to implement the interprocess communication.
// KNOWN USES:
// - Network Traffic Management.
// - Mobile Robot.
// CONSEQUENCES:
// benefits:
// - Separation of concerns.
// - Supportfor change and extension.
// - Support for multi - tasking.
// liabilities:
// - Increased system complexity.
// - Complex control component.
// - Eficiency.
// - Applicability.
// See also:
// - Model-View-Controller.

// 2.5 Adaptable Systems
// Systems evolve over time-new functionality is added and existing services are changed.
// - The Microkernel pattern.
// - The Reflection pattern.

// Microkernel.
// The Microkernel architectural pattern applies to software systems that must be able to adapt to changing system requirements.It separates a minimal functional core from extended functionality and customer - specific parts.The microkernel also sexves as a socket for plugging in these extensions and coordinating their collaboration.
// EXAMPLE:
// Suppose we intend to develop a new operating system for desktop computers called Hydra.
// CONTEXT:
// The development of several applications that use similar programming interfaces that build on the same core functionality.
// PROBLEM:
// Developing software for an application domain that needs to cope with a broad spectrum of similar standards and technologies is a nontrivial task.
// forces:
// - The application platform must cope with continuous hardware and software evolution.
// - The application platform should be portable, extensible and adaptable to allow easy integration of emerging technologies.
// - The applications in your domain need to support different, but similar, application platforms.
// - The applications may be categorized into groups that use the same functional core in different ways, requiring the underlying application platform to emulate existing standards.
// - The functional core of the application platform should be separated into a component with minimal memory size, and services that consume as little processing power as possible.
// SOLUTION:
// Encapsulate the fundamental services of your application platform in a microkernel component.
// External servers implement their own view of the underlying microkernel.
// Clients communicate with external servers by using the communication facilities provided by the microkernel.
// STRUCTURE:
// - Internal servers
// - External servers
// - Adapters
// - Clients
// - Microkernel
// class: Microkernel
// Responsibility:
// -Provides core mechanisms.
// - Offers communication facilities.
// - Encapsulates system dependencies.
// - Manages and controls resources.
// Collaborators:
// - Internal Server

// An internal server - also known as a subsystem - extends the functionality provided by the microkernel.
// class: Internal Server
// Responsibility:
// - Implements additional services.
// - Encapsulates some system specifics.
// Collaborators:
// - Microkemel

// One of the design goals should be to keep the microkernel as small as possible to reduce memory requirements.Another goal is to provide mechanisms that execute quickly, to reduce service execution time.
// use internal server for that.
// An external seruer-also known as a personality-is a component that uses the microkernel for implementing its own view of the underlying application domain.

// class: External Server
// Resgonsibility:
// - Provides programming interfaces for its clients.
// Collaborators:
// - Microkernel.

// A client is an application that is associated with exactly one external server.
// Adapters - represent these interfaces between clients and their external servers

// class: Client
// Responsibility: Represents an application
// Collaborators: adapter.

// class: Adapter
// Responsibility:
// - Hides system dependencies such as communication facilities from the client.
// - Invokes methods of external servers on behalf of clients.
// Collaborators:
// - External Server
// - Microkernel

// DYNAMICS:
// The dynamic behavlor of a Microkernel system depends on the functionality it provides for inter - process communication.

// IMPLEMENTATION:
// 1. Analyze the application domain.
// 2. Analyze external servers.
// 3. Categorize the services.
// 4. Partition the categories.
// 5. Find a consistent and complete set of operatims and abstractims for every category you identified in step 1.
// For example, we provide services for:
// - Creating and terminating processes and threads.
// - Stopping and restarling them.
// - Reading from or writing to process address spaces.
// - Catching and handling exceptions.
// - Managing relationships between processes or threads.
// - Synchronizing and coordinating threads.
// 6. Determine strategies for request transmission and retrieval.
// Compare design patterns such as Forwarder - Receiver and Client - Dispatcher - Server for more information on the implementation of communication mechanisms.
// 7. Structure the microkernel component.
// If possible, design the microkernel using the Layers pattern to separate system - specific parts from system - independent parts.
// 8. To specla the programming interfaces of the microkernel, you need to decide how these interfaces should be accessible externally.
// 9. The microkernel is responsible for managing all system resources such as memory blocks, devices or device contexts.
// 10. Design and implement the internal ser-uers as separate processes or shared libraries.
// - Active servers are implemented as processes.
// - Passive servers as shared libraries.
// 11. Implement the external servers.
// 12. Implement the adapters.
// See the Proxy pattern for benefits and pitfalls of caching.
// 13. Develop client applications or use existing ones for the ready-to-run Microkernel system.
// EXAMPLE RESOLVED:
// - Building an external server;
// - Providing an adapter that is designed as a library, dynamically linked to clients
// - implementing the internal sewers required for MacOS.
// VARIANTS:
// - Microkernel System with indirect Client-Server connections;
// - Distributed Microkernel System.
// KNOWN USES:
// - Mach operating system;
// - Amoeba
// - Chorus
// - Windows NT
// - MKDE
// CONSEQUENCES:
// benfits:
// - Portability
// - Flexibility and Extensibility
// - Separation of policy and mechanism
// - Scalability
// - Reliability.
// - Transparency.
// liabilities:
// - Perjiormance
// - Complexity of design and implementation.
// SEE ALSO:
// - Broker, Reflection, Layers.
// The lowest layer includes the database management system.
// The middle layer contains the business logic.
// The highest layer comprises different business applications.

// Reflection.
// The Reflectton architectural pattern provldes a mechanism for changing structure and behavior of software systems dynamically
// A meta level provides information about selected system properties and makes the software self - aware. A base level includes the application logic.
// ALSO KNOWN AS:
// Open Implementation, Meta-Level Architecture.
// EXAMPLE:
// Consider a C++ application that needs to write objects to disk and read them in again.
// CONTEXT:
// Building systems that support their own modification a priori.
// PROBLEM:
// forces:
// - Changing software is tedious, error prone, and often expensive.
// - Adaptable software systems usually have a complex inner structure.
// - The more techniques that are necessary for keeping a system changeable, such as parameterization, subclassing, mix - ins, oreven copy and paste, the more awkward and complex its modification becomes.
// - Changes can be of any scale.
// - Even fundamental aspects of software systems can change.
// SOLUTION:
// - Make the software self-aware, and make selected aspects of its structure and behavior accessible for adaptation and change.
// This leads to an architecture that is split into two major parts : a meta level and a base level.
// An interface is specified for manipulating the metaobjects.It is called the metaobject protocol.
// STRUCTURE:
// The meta level consists of a set of metaobjects. There are three sources for such information :
// - It can be provided by the run-time environment of the system, such as C++ type identification objects.
// - It can be user-defined, such as the function call mechanism in the previous section.
// - It can be retrieved from the base level at run-time, for example information about the current state of computation
// The base level models and implements the application logic of the software.

// class: Base Level
// Responsibility:
// - Implements the application logic.
// - Uses information provided by the meta level.
// Collaborators:
// - Meta level.

// class: Meta Level.
// Responsibility:
// Encapsulates system internals that may change.
// Provides an interface to facilitate modifications to the meta - level. 
// Collaborators: Base Level
// class: Metaobject Protocol
// Responsibility:
// - Offers an interface for specifying changes to the meta level
// - Performs specified changes
// Collaboratots:
// - Meta Level
// - Base Level

// DYNAMICS:

// IMPLEMENTATION:
// 1. Define a model of the application.
// - Which services should the software provide ?
// - Which components can fulfil these services ?
// - What are the relationships between the components ?
// - How do the components cooperate or collaborate ?
// - What data do the components operate on ?
// - How will the user interact with the software ?
// 2. Identify varying behavior.
// - Real-time constraints, such as deadlines, time-fence protocols and algorithms for detecting deadline misses.
// - Transaction protocols, for example optimistic and pessimistic transaction control in accounting systems.
// - Inter-process communication mechanisms, such as remote procedure calls and shared memory.
// - Behavior in case of exceptions, for example the handling of deadline misses in real-time systems.
// - Algorithms for application services, such as country-specific VAT calculation.
// 3. Identify structural aspects of the system.
// 4. Identify system services.
// - exception handling
// - Resource allocation
// - Garbage collection
// - Page swapping
// - Object creation
// 5. Define the metaobjects.
// 6. Define the metaobject protocol.
// There are two options for implementing the metaobject protocol :
// - Integrate it with the metaobjects.Every metaobject provides those functions of the metaobject protocol that operate on it.
// - Implement the metaobject protocol as a separate component.
// 7. Dew the base level.

// EXAMPLE RESOLVED.
// VARIANTS:
// - ReJection with several meta levels.

// KNOWN USES:
// - CLOS.
// - MIP.
// - PGen.
// - NEDIS.
// - OLE 2.0.

// CONSEQUENCES:
// benefits:
// - No explicit mod$cation of source code.
// - Changing a software system is easy.
// - Support for many kinds of change.
// liabilities:
// - Modifications at the meta level may cause damage.
// - Increased number of components.
// - Lower efficiency.
// - Not all potential changes to the software are supported.
// - Not all languages support reflection.

// SEE ALSO:
// - Microkernel architectural pattern.

// practice with all patterns, learn something new if needed. !!!
	}

	// Design Patterns
	// 3.1 Introduction.
	// Design patterns are medium-scale patterns.
	// groups:
	// - Structural Decomposition
	// The Whole-Part pattern.
	// - Organization of Work.
	// Master-Slave pattern.
	// - Access Control.
	// Proxy pattern.
	// - Management.
	// the Command Processor pattern, View Handler pattern
	// - Communication.
	// the Forwarder-Receiver pattern, Client-Dispatcher-Server pattern, The Publisher-Subscriber(Event Channel variant).

	// 3.2 Structural Decomposition.
	// THE WHOLE - PART DESIGN PATTERN.




	namespace chapter3
	{
		void main();
	}
}
