#include "ASystemOfPatterns.h"

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
			// Layers
			DataLink datalink;
			Transport transport;
			Session session;

			transport.setLowerLayer(&datalink);
			session.setLowerLayer(&transport);

			session.L3Service();
		}
	}
}