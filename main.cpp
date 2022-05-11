#include <iostream>

#include "hip/hip_runtime.h"

#include "popl.hpp"
#include "Assert.hpp"

int main(int argc, const char *argv[])
{
    HIP_ASSERT(false, "Dupa %s, %d", "dupa jasiu", 12);
    float f;

    int m, i;
    bool v;

    popl::OptionParser op("Allowed options");
    auto help_option = op.add<popl::Switch>("h", "help", "produce help message");
    auto groff_option = op.add<popl::Switch>("", "groff", "produce groff formatted help message");
    auto bash_option = op.add<popl::Switch>("", "bash", "produce bash completion script");
    auto verbose_option = op.add<popl::Switch, popl::Attribute::optional>("v", "verbose", "be verbose", &v);
    auto hidden_option = op.add<popl::Switch, popl::Attribute::hidden>("x", "", "hidden option");
    auto double_option = op.add<popl::Value<double>>("d", "double", "test for double values", 3.14159265359);
    auto float_option = op.add<popl::Value<float>>("f", "float", "test for float values", 2.71828182845f, &f);
    
    //op.add<popl::Value<int>>("i", "int", "test for int value w/o option", 23, &i);
    
    auto string_option = op.add<popl::Value<std::string>>("s", "string", "test for string values");
    auto implicit_int_option = op.add<popl::Implicit<int>>("m", "implicit", "implicit test", 42);
    auto advanced_option = op.add<popl::Switch, popl::Attribute::advanced>("", "advanced", "advanced option");
    auto expert_option = op.add<popl::Switch, popl::Attribute::expert>("", "expert", "expert option");
    auto inactive_option = op.add<popl::Switch>("", "inactive", "inactive option");
    inactive_option->set_attribute(popl::Attribute::inactive);
    implicit_int_option->assign_to(&m);

    try
    {
        op.parse(argc, argv);
    }
    catch (const popl::invalid_option &e)
    {
        std::cerr << "Invalid Option Exception: " << e.what() << "\n";
        std::cerr << "error:  ";
        if (e.error() == popl::invalid_option::Error::missing_argument)
            std::cerr << "missing_argument\n";
        else if (e.error() == popl::invalid_option::Error::invalid_argument)
            std::cerr << "invalid_argument\n";
        else if (e.error() == popl::invalid_option::Error::too_many_arguments)
            std::cerr << "too_many_arguments\n";
        else if (e.error() == popl::invalid_option::Error::missing_option)
            std::cerr << "missing_option\n";

        if (e.error() == popl::invalid_option::Error::missing_option)
        {
            std::string option_name(e.option()->name(popl::OptionName::short_name, true));
            if (option_name.empty())
                option_name = e.option()->name(popl::OptionName::long_name, true);
            std::cerr << "option: " << option_name << "\n";
        }
        else
        {
            std::cerr << "option: " << e.option()->name(e.what_name()) << "\n";
            std::cerr << "value:  " << e.value() << "\n";
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}