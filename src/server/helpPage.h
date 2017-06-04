#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct EnpPoint
{
	bool isServerOrClient; //=false;
	std::string address;// = "";
	int port;// = 0;
};

struct EnpPoint parseArgs(int ac, char *av[] ){

	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help,h", "produce help message")
	    ("server,s", "запустить игру как сервер")
	    ("client,c", po::value<std::string>(), "запустить игру как клиент к адрессу <address>")
	    ("port,p", po::value<int>(), "<port>") //->required()
	;

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);

	struct EnpPoint ep;

	if (vm.count("help"))
	{
	    std::cout << desc << "\n";
	    // return 1;//Выход
	}

	if (vm.count("server"))
	{
		std::cout << "Заущен как сервер" << ".\n";
		ep.isServerOrClient = true;
		
		if (vm.count("port"))
			int port = vm["port"].as<int>();
		else{
		    std::cout << "Вы не указали порт!" << ".\n";
		    // return 1;//Выход
		}
	}
	if (vm.count("client")) //Не проверяется отсутствие адресса при вводе
	{
		std::cout << "Заущен как клиент, подключённый по адрессу " << vm["client"].as<std::string>() << ".\n";
		std::string address = vm["client"].as<std::string>();
		ep.isServerOrClient = true;
		
		if (vm.count("port"))
			int port = vm["port"].as<int>();
		else{
		    std::cout << "Вы не указали порт!" << ".\n";
		    // return 1;//Выход
		}
	}

	// try {


	// } catch ( const std::exception& e ) {
		// std::cerr << e.what() << std::endl;
		// return 1;
	// }

	return ep;
}