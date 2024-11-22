#include <roo.hpp>

#include <iostream>

class MyApp : public roo::Application
{
public:
				MyApp()
				{
								std::cout << "wassup" << std::endl;
								
				}
};

roo::Application* roo::CreateApplication()
{
				return new MyApp();
}