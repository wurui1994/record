// wget https://github.com/nbsdx/SimpleJSON/raw/master/json.hpp
// g++ simplejson_example.cpp && ./a.out

#include "json.hpp"
#include <iostream>

using json::JSON;

int main() 
{
    JSON obj = {
        "arrayOne", json::Array( true, "Two", 3, 4.0 ),
        "object", {
            "inner", "Inside"
        },
        "nested", { 
            "some", { 
                "deep", { 
                    "key", "Value" 
                } 
            } 
        },
        "arrayTwo", json::Array( false, "three" )
    };
    if(obj.JSONType() == JSON::Class::Object)
    {
        for(auto const& ele:obj.ObjectRange())
        {
            std::cout << ele.first << ":" << ele.second << std::endl;
        }
    }
    else
    {
        for(auto const& ele:obj.ArrayRange())
        {
            std::cout << ele << std::endl;
        } 
    }

    std::cout << obj.size() << std::endl;
    std::cout << obj["array"] << std::endl;
}