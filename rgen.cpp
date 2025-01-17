// inspired by the programs posted by PROF on github i.e using_exec.cpp, using_pipe.cpp, using_rand.cpp, using_getopt.cpp

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace my_demo_namespace
{
    template < typename T > std::string convert_coords_from_int_to_string(const T& take_input )
    {
        std::ostringstream makestring;
        makestring << take_input;
        return makestring.str();
    }
}

unsigned int num_of_streets (unsigned int k )
{
    std::ifstream urandom("/dev/urandom"); //open dev/urandom
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int num = 3; //
    urandom.read((char*)&num, sizeof(unsigned int));
    num = num % (k+1-2) +2;  //to make random number lie between max and min: rand() % (max_number + 1 - minimum_number) + minimum_number // stack overflow

    urandom.close();
    return (unsigned int) num;
}

void street_names(std::vector<std::string> &streetnames , unsigned int number_of_streets)
{
    std::string sname = "street";
    for (unsigned int j = 0; j < number_of_streets; j++){
        streetnames.push_back(sname);
        sname = sname + 'j';
    }
}

int maximum_of_coordinates(int coordx, int coordy)
{
    int maxc;
    if(coordx > coordy)
        maxc=coordx;
    else
        maxc=coordy;
    return maxc;
}

unsigned int num_of_line_segments (unsigned int k)
{
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int num = 3;
    urandom.read((char*)&num, sizeof(unsigned int));
    num = num % (k + 1 - 1) + 1;   //rand() % (max_number + 1 - minimum_number) + minimum_number // stack overflow

    urandom.close();
    return (unsigned int) num;
}

int minimum_of_coordinates(int coordx, int coordy)
{
    int minc;
    if(coordx < coordy)
        minc=coordx;
    else
        minc=coordy;
    return minc;
}

int cxy_values (unsigned int k)
{
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int num = 3;
    urandom.read((char*)&num, sizeof(int));
    num = num % (k + k);  //rand() % (max_number + 1 - minimum_number) + minimum_number // stack overflow
    int o= num - k ;

    urandom.close();
    return o;
}

unsigned int waiting_time (unsigned int k)
{
    std::ifstream urandom("/dev/urandom");
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
    unsigned int num = 3;
    urandom.read((char*)&num, sizeof(unsigned int));
    num = num % (k + 1 - 5) + 5;  //rand() % (max_number + 1 - minimum_number) + minimum_number // stack overflow

    urandom.close();
    return (unsigned int) num;
}

bool intersection_cond(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    double xnum, xden, ynum, yden, intpointx, intpointy;

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4));
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
    intpointx = xnum / xden;

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4);
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    intpointy = ynum / yden;

    int min_x_of_line1, min_x_of_line2, max_x_of_line1, max_x_of_line2, min_y_of_line1, min_y_of_line2, max_y_of_line1, max_y_of_line2;

    min_x_of_line1 = minimum_of_coordinates(x1, x2);
    max_x_of_line1 = maximum_of_coordinates(x1, x2);
    min_x_of_line2 = minimum_of_coordinates(x3, x4);
    max_x_of_line2 = maximum_of_coordinates(x3, x4);
    min_y_of_line1 = minimum_of_coordinates(y1, y2);
    max_y_of_line1 = maximum_of_coordinates(y1, y2);
    min_y_of_line2 = minimum_of_coordinates(y3, y4);
    max_y_of_line2 = maximum_of_coordinates(y3, y4);

    if (min_x_of_line1 <= intpointx && intpointx <= max_x_of_line1)
        if (min_x_of_line2 <= intpointx && intpointx <= max_x_of_line2)
            if (min_y_of_line1 <= intpointy && intpointy <= max_y_of_line1)
                if (min_y_of_line2 <= intpointy && intpointy <= max_y_of_line2)
                    return true;
    return false;
}

bool add_coord_cond (std::vector<int> xy_coord_vec, int x, int y)
{
    int size_coordvec = xy_coord_vec.size();
    if ( xy_coord_vec.empty()){
        return true; // 1st point of any street will always be added
    }
    if (size_coordvec == 2){
        if ((x == xy_coord_vec[0]) && (y == xy_coord_vec[1]) ) {
            return false;
        }
        return true;
    }
    else{
        for (unsigned int j = 0; j < xy_coord_vec.size(); j = j + 2){
            if (x == xy_coord_vec[j] && y == xy_coord_vec[j + 1]){  // if randomly generated coord are not distinct, they won't be added
                return false;
            }
        }

        double p1, p2;

        if (x == xy_coord_vec[size_coordvec - 2] && x == xy_coord_vec[size_coordvec - 4])
            return false;
        if ((x == xy_coord_vec[size_coordvec - 2]) && (x != xy_coord_vec[size_coordvec - 4]))
        {
            if (size_coordvec == 4)
                return true;
            else
            {
                for (int i = size_coordvec - 3; i >= 2; i = i - 2 )
                {
                    if (intersection_cond(x, y, xy_coord_vec[size_coordvec - 2], xy_coord_vec[size_coordvec - 1], xy_coord_vec[i - 1],
                                          xy_coord_vec[i], xy_coord_vec[i - 3], xy_coord_vec[i - 2]))
                        return false;
                }
                return true;
            }
        }
        if ((xy_coord_vec[size_coordvec - 4] == xy_coord_vec[size_coordvec - 2]) && (x != xy_coord_vec[size_coordvec - 2]))
        {
            if (size_coordvec == 4)
                return true;
            else
            {
                for (int i = size_coordvec - 3; i >= 0; i = i - 2 )
                {
                    if (intersection_cond(x, y, xy_coord_vec[size_coordvec - 2], xy_coord_vec[size_coordvec - 1], xy_coord_vec[i - 1],
                                          xy_coord_vec[i], xy_coord_vec[i - 3], xy_coord_vec[i - 2]))
                        return false;
                }
                return true;
            }
        }

        p1 = ((y - xy_coord_vec[size_coordvec - 1]) / (x - xy_coord_vec[size_coordvec - 2]));
        p2 = ((xy_coord_vec[size_coordvec - 1]) - xy_coord_vec[size_coordvec - 3]) / (xy_coord_vec[size_coordvec - 2] - xy_coord_vec[size_coordvec - 4]);

        if (p1 == p2)
            return false;
        else
        {
            if (size_coordvec == 4)
                return true;
            else
            {
                for (int m = size_coordvec - 3; m >= 0; m = m - 2 )
                {
                    if (intersection_cond(x, y, xy_coord_vec[size_coordvec - 2], xy_coord_vec[size_coordvec - 1], xy_coord_vec[m - 1],
                                          xy_coord_vec[m], xy_coord_vec[m - 3], xy_coord_vec[m - 2]))
                        return false;
                }
                return true;
            }
        }
    }
}


int main (int argc, char **argv) {

    std::vector<int> xy_coordinates;
    std::vector<int> lines_in_street;
    std::vector<std::string> streetnames;
    unsigned int n_value_int = 5, l_value_int = 5, s_value_int = 10, c_value_int = 20, wait_time;
    std::string value_s, value_n, value_l, value_c;
    int cli_arg, streetnumber, num_of_linseg_in_a_street, x_coordinate, y_coordinate;

    opterr = 0; // so that it does not print error msges on its own
    while ((cli_arg = getopt(argc, argv, ":s:n:l:c:")) != -1) { //since all cli args are optional
        switch (cli_arg) {

            case 's':
                value_s = optarg;
                s_value_int = std::atoi(value_s.c_str());
                if (s_value_int < 2){
                    std::cerr << "Error: Minimum number of streets should be 2!"<<std::endl;
                    exit(1);
                }
                break;

            case 'n':
                value_n = optarg;
                n_value_int = std::atoi(value_n.c_str());
                if (n_value_int < 1){
                    std::cerr << "Error: Minimum number of line segments should be 1!"<<std::endl;
                    exit(1);
                }
                break;

            case 'l':
                value_l = optarg;
                l_value_int = std::atoi(value_l.c_str());
                if (l_value_int < 5){
                    std::cerr << "Error: Minimum wait time should be 5 seconds!"<<std::endl;
                    exit(1);
                }
                break;

            case 'c':
                value_c = optarg;
                c_value_int = std::atoi(value_c.c_str());
                if (c_value_int < 1){
                    std::cerr << "Error: Co-ordinate values lie in [-k,k], where k should be greater than equal to 1!"<<std::endl;
                    exit(1);
                }
                break;

            case ':':
                if (optopt == 's') {
                    std::cerr << "Error: -" <<optopt<< " specified but its value is missing!" << std::endl;
                    break;
                }
                else if (optopt == 'n') {
                    std::cerr << "Error: -" <<optopt<< " specified but its value is missing!" << std::endl;
                    break;
                }
                else if (optopt == 'l') {
                    std::cerr << "Error: -" <<optopt<< " specified but its value is missing!" << std::endl;
                    break;
                }
                else if (optopt == 'c') {
                    std::cerr << "Error: -" <<optopt<< " specified but its value is missing!" << std::endl;
                    break;
                }
                break;

            case '?':
                std::cerr << "Error: -" <<optopt<<" Unrecognised option is specified! "<< std::endl;
                break;
        }
    }

    while (true)
    {
        if ( !streetnames.empty()){
            for(std::vector<std::string>::iterator it = streetnames.begin(); it != streetnames.end(); it++){
                std::cout<<"r "<<'"'<<*it<<'"'<<std::endl;
            }
            streetnames.clear();
            lines_in_street.clear();
        }

        streetnumber = num_of_streets(s_value_int); // getting a random street number value

        for (int i = 0; i < streetnumber; i++){
            num_of_linseg_in_a_street = num_of_line_segments(n_value_int); // getting a random line segment number for a street
            lines_in_street.push_back(num_of_linseg_in_a_street); //adding nuumber of line segs in each st in a vector
        }

        street_names(streetnames, streetnumber); //assigning names to streets

        int st_name_it = 0;

        for (unsigned int j = 0; j < lines_in_street.size(); j++) // iterating streets 1 by 1
        {
            xy_coordinates.clear();
            int num_points_iterator = 0, err_num = 0;
            while (num_points_iterator < lines_in_street[j] + 1 ) // no. of coords is 1 plus num of line segs
            {
                x_coordinate = cxy_values(c_value_int); // assigning a random value to x coord
                y_coordinate = cxy_values(c_value_int);
                //std::cout<<x_coordinate<<"  "<<y_coordinate<<std::endl;
                if (add_coord_cond(xy_coordinates, x_coordinate, y_coordinate))  // if all conditions are satisfied and point is added
                {
                    num_points_iterator++;
                    xy_coordinates.push_back(x_coordinate);
                    xy_coordinates.push_back(y_coordinate);
                    err_num = 0;
                }
                else
                {
                    if (err_num == 25)
                    {
                        std::cerr<<"Error: Failed to generate a valid input for 25 simultaneous attempts! "<<std::endl;
                        exit(1);
                    }
                    err_num++;
                }
            }

            std::string add_st_output = std::string("a \"") + streetnames[st_name_it] + "\" ";

            for (unsigned int it = 0; it < xy_coordinates.size(); it = it + 2) //because i'm storing x first then y, therefore 1 point(X,Y) is stored in 2 locs
            {
                std::string a,b;
                if (xy_coordinates[it] < 0){
                    a = "-" + my_demo_namespace::convert_coords_from_int_to_string(xy_coordinates[it] * (-1));//make positive when send to str conversion and put - infront
                } else {
                    a = my_demo_namespace::convert_coords_from_int_to_string(xy_coordinates[it]);
                }
                if (xy_coordinates[it + 1] < 0){
                    b = "-" + my_demo_namespace::convert_coords_from_int_to_string(xy_coordinates[it + 1] * (-1));// for y
                } else {
                    b = my_demo_namespace::convert_coords_from_int_to_string(xy_coordinates[it + 1]);
                }
                add_st_output = add_st_output + '(' + a + ',' + b + ')';
            }

            std::cout << add_st_output << std::endl;
            st_name_it++;
        }

        std::cout<<'g'<<std::endl;
        wait_time = waiting_time(l_value_int); // randomly initialise a waiting time
        usleep(wait_time * 1000000);
    }
    return 0;
}

//
// Created by Jannat Sidhu on 2019-11-03.
//


