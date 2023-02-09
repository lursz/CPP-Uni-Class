#include "class.h"
#include <sstream>
#include <vector>
int main()
{
    std::vector<Object *> vector_of_objects;
    std::string input;
    std::cout << std::setprecision(6) << std::fixed;

    while (std::cin.eof() == false)
    {

        std::getline(std::cin, input);
        switch (input[0])
        {
        //* --------------------------------------------------------
        //*                          ADD
        //* --------------------------------------------------------
        case 'a':
        {
            switch (input[4])
            {
            //* ---------------------- string --------------------------
            case 'S':
            {
                StringObject *s = new StringObject(input.substr(17));
                vector_of_objects.push_back(s);
                break;
            }
            //* ---------------------- double --------------------------
            case 'D':
            {
                double temp = stod(input.substr(17));
                DoubleObject *d = new DoubleObject(temp);
                vector_of_objects.push_back(d);
                break;
            }
            //* ---------------------- complex -------------------------
            case 'C':
            {
                input = input.substr(18);
                int re = 0, im = 0;


                // i
                if (input[0] == 'i')
                {
                    std::complex<int> temp(0, 1);
                    ComplexObject *c = new ComplexObject(temp);
                    vector_of_objects.push_back(c);
                }
                // real only
                else if (input[input.size() - 1] != 'i')
                {
                    re = stoi(input.substr(0, input.size()));
                    im = 0;

                    std::complex<int> temp(re, im);
                    ComplexObject *c = new ComplexObject(temp);
                    vector_of_objects.push_back(c);
                }
                else
                for (int i = 0; input[i] != 0; i++)
                {
                    if (input[i] == '+')
                    {

                        re = stoi(input.substr(0, i));
                        im = stoi(input.substr(i, input.length() - i - 1));

                        std::complex<int> temp(re, im);
                        ComplexObject *c = new ComplexObject(temp);
                        vector_of_objects.push_back(c);
                        break;
                    }
                    else if (input[i] == '-')
                    {
                        re = stoi(input.substr(0, i));
                        im = stoi(input.substr(i, input.length() - i - 1));

                        std::complex<int> temp(re, im);
                        ComplexObject *c = new ComplexObject(temp);
                        vector_of_objects.push_back(c);
                        break;
                    }
                    else if (input[i] == 'i')
                    {
                        re = 0;
                        im = stoi(input.substr(0, i));

                        std::complex<int> temp(re, im);
                        ComplexObject *c = new ComplexObject(temp);
                        vector_of_objects.push_back(c);
                        break;
                    }
                }

                break;
            }
            //* ---------------------- int --------------------------
            case 'I':
            {
                int temp = stoi(input.substr(14));
                IntObject *i = new IntObject(temp);
                vector_of_objects.push_back(i);
                break;
            }
            }
            break;
        }
            //* --------------------------------------------------------
            //*                          SUM
            //* --------------------------------------------------------
        case 's':
        {
            if (input.length() == 3)
            {
                ComplexObject::print_sum();
                DoubleObject::print_sum();
                IntObject::print_sum();
                StringObject::print_sum();
            }
            else
            {
                switch (input[4])
                {
                case 'S':
                {
                    StringObject::print_sum();
                    break;
                }
                case 'D':
                {
                    DoubleObject::print_sum();
                    break;
                }
                case 'C':
                {
                    ComplexObject::print_sum();
                    break;
                }
                case 'I':
                {
                    IntObject::print_sum();
                    break;
                }
                }
            }
            break;
        }
        //* --------------------------------------------------------
        //*                       MULTIPLY
        //* --------------------------------------------------------
        case 'm':
        {
            int multiplayer = stoi(input.substr(4));

            for (int i = 0; i < vector_of_objects.size(); i++)
            {
                vector_of_objects[i]->multiply(multiplayer);
            }

            break;
        }
        //* --------------------------------------------------------
        //*                          GET
        //* --------------------------------------------------------
        case 'g':
        {
            int index = stoi(input.substr(4));
            vector_of_objects[index]->print_value();
            break;
        }
        }
    }
    return 0;
}