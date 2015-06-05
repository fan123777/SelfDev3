#pragma once

#include<iostream>
#include<list>

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

		// From Mud to Structure
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
		// - Cascades ofchanging behavior.
	}
}
