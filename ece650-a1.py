import ast
from decimal import Decimal

import sys
import re

Streets = {}

def Generate_output():
    street_1 = 1
    street_2 = 1

    street_endpoints = []
    int_points = []
    edges_final = []
    edges_repeat_1 = []
    edges_repeat_2 = []
    vert_int = []
    temp_1 = []
    int_points_list_m = []

    edge_set = set()
    graph_set = set()

    vertices_dict = {}

    list_val = list(Streets.values())
    num_streets = len(list_val)
    street_endpoints = [None] * num_streets

    for each in range(0, num_streets):
        temp_1 = [i.split(', ', 1)[0] for i in list_val[each]]
        street_endpoints[each] = temp_1

    for i in range(0, num_streets):
        length_st1 = len(street_endpoints[i])

        for j in range(i + 1, num_streets):
            length_st2 = len(street_endpoints[j])
            while street_1 < length_st1:
                while street_2 < length_st2:
                    source_1 = street_endpoints[i][street_1 - 1]
                    dest_1 = street_endpoints[i][street_1]
                    source_2 = street_endpoints[j][street_2 - 1]
                    dest_2 = street_endpoints[j][street_2]

                    source_1_x, source_1_y = ast.literal_eval(source_1)
                    dest_1_x, dest_1_y = ast.literal_eval(dest_1)
                    source_2_x, source_2_y = ast.literal_eval(source_2)
                    dest_2_x, dest_2_y = ast.literal_eval(dest_2)

                    source_1_x = float("{0:.2f}".format(source_1_x))
                    source_1_y = float("{0:.2f}".format(source_1_y))
                    dest_1_x = float("{0:.2f}".format(dest_1_x))
                    dest_1_y = float("{0:.2f}".format(dest_1_y))
                    source_2_x = float("{0:.2f}".format(source_2_x))
                    source_2_y = float("{0:.2f}".format(source_2_y))
                    dest_2_x = float("{0:.2f}".format(dest_2_x))
                    dest_2_y = float("{0:.2f}".format(dest_2_y))

                    min_x_of_point = min(source_1_x, dest_1_x);
                    min_x_of_point2 = min(source_2_x, dest_2_x);
                    max_x_of_point = max(source_1_x, dest_1_x);
                    max_x_of_point_2 = max(source_2_x, dest_2_x);
                    min_y_of_point = min(source_1_y, dest_1_y);
                    min_y_of_point2 = min(source_2_y, dest_2_y);
                    max_y_of_point = max(source_1_y, dest_1_y);
                    max_y_of_point2 = max(source_2_y, dest_2_y);

                    dsy1 = dest_1_y - source_1_y
                    sdx1 = source_1_x - dest_1_x
                    res1 = dsy1 * (source_1_x) + sdx1 * (source_1_y)

                    dsy2 = dest_2_y - source_2_y
                    sdx2 = source_2_x - dest_2_x
                    res2 = dsy2 * (source_2_x) + sdx2 * (source_2_y)

                    det = dsy1 * sdx2 - dsy2 * sdx1

                    source_1 = "(" + str(source_1_x) + "," + str(source_1_y) + ")"
                    dest_1 = "(" + str(dest_1_x) + "," + str(dest_1_y) + ")"
                    source_2 = "(" + str(source_2_x) + "," + str(source_2_y) + ")"
                    dest_2 = "(" + str(dest_2_x) + "," + str(dest_2_y) + ")"
                    l_pairs = list((source_1, dest_1, source_2, dest_2))

                    flag_1 = False;  flag_2 = False

                    if (det != 0):
                        X = Decimal((sdx2 * res1 - sdx1 * res2) / det);  X = round(X, 2)
                        Y = Decimal((dsy1 * res2 - dsy2 * res1) / det);  Y = round(Y, 2)

                        if (bool(X <= max_x_of_point) & bool(X >= min_x_of_point)):
                            if (bool(Y <= max_y_of_point) & bool(Y >= min_y_of_point)):
                                flag_1 = True
                            if (bool(X <= max_x_of_point_2) & bool(X >= min_x_of_point2)):
                                if (bool(Y <= max_y_of_point2) & bool(Y >= min_y_of_point2)):
                                    flag_2 = True
                        if (flag_1 == True & flag_2 == True):

                            new_v = "(" + str(X) + "," + str(Y) + ")"
                            int_points.extend(l_pairs)
                            int_points_list_m.append(new_v)
                            vert_int.append(l_pairs)
                            int_points.append(new_v)
                            graph_set = set(int_points)
                            int_points = list(graph_set)
                            for each in range(0, len(int_points)):
                                vertices_dict[each] = int_points[each]
                        else:
                            pass
                    elif (source_1 == dest_2):
                        new_v = "(" + str(dest_2_x) + "," + str(dest_2_y) + ")"
                        int_points.extend(l_pairs)
                        int_points_list_m.append(new_v)
                        vert_int.append(l_pairs)
                        int_points.append(new_v)
                        graph_set = set(int_points)
                        int_points = list(graph_set)
                        for each in range(0, len(int_points)):
                            vertices_dict[each] = int_points[each]

                    elif (dest_1 == source_2):
                        new_v = "(" + str(source_2_x) + "," + str(source_2_y) + ")"
                        int_points.extend(l_pairs)
                        int_points_list_m.append(new_v)
                        vert_int.append(l_pairs)
                        int_points.append(new_v)
                        graph_set = set(int_points)
                        int_points = list(graph_set)
                        for each in range(0, len(int_points)):
                            vertices_dict[each] = int_points[each]

                    elif (source_1_x == dest_1_x == source_2_x == dest_2_x):
                        y_range1 = abs(dest_1_y - source_1_y)
                        y_range2 = abs(dest_2_y - source_2_y)
                        if (y_range1 > y_range2):
                            main_line_b = 1
                        elif (y_range2 > y_range1):
                            main_line_b = 2
                        if (main_line_b == 1):
                            if (source_2_y > min_y_of_point and source_2_y < max_y_of_point):
                                new_v = "(" + str(source_2_x) + "," + str(source_2_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]
                            if (dest_2_y > min_y_of_point and dest_2_y < max_y_of_point):
                                new_v = "(" + str(dest_2_x) + "," + str(dest_2_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]

                        if (main_line_b == 2):
                            if (source_1_y > min_y_of_point2 and source_1_y < max_y_of_point2):
                                new_v = "(" + str(source_1_x) + "," + str(source_1_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]
                            if (dest_1_y > min_y_of_point2 and dest_1_y < max_y_of_point2):
                                new_v = "(" + str(dest_1_x) + "," + str(dest_1_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]

                    elif (source_1_y == dest_1_y == source_2_y == dest_2_y):
                        x_range1 = abs(dest_1_x - source_1_x)
                        x_range2 = abs(dest_2_x - source_2_x)
                        if (x_range1 > x_range2):
                            main_line_b = 1
                        elif (x_range2 > x_range1):
                            main_line_b = 2
                        if (main_line_b == 1):
                            if (source_2_x > min_x_of_point and source_2_x < max_x_of_point):
                                new_v = "(" + str(source_2_x) + "," + str(source_2_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]
                            if (dest_2_x > min_x_of_point and dest_2_x < max_x_of_point):
                                new_v = "(" + str(dest_2_x) + "," + str(dest_2_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]

                        if (main_line_b == 2):
                            if (source_1_x > min_x_of_point2 and source_1_x < max_x_of_point_2):
                                new_v = "(" + str(source_1_x) + "," + str(source_1_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]
                            if (dest_1_x > min_x_of_point2 and dest_1_x < max_x_of_point_2):
                                new_v = "(" + str(dest_1_x) + "," + str(dest_1_y) + ")"
                                int_points.extend(l_pairs)
                                int_points_list_m.append(new_v)
                                vert_int.append(l_pairs)
                                int_points.append(new_v)
                                graph_set = set(int_points)
                                int_points = list(graph_set)
                                for each in range(0, len(int_points)):
                                    vertices_dict[each] = int_points[each]

                    street_2 = street_2 + 1
                street_1 = street_1 + 1
                street_2 = 1
            street_1 = 1

    sys.stdout.write("V ")
    sys.stdout.flush()
    sys.stdout.write(str(len(vertices_dict))+'\n')
    sys.stdout.flush()

    for each in range(0, len(int_points_list_m)):
        intersection_pt = int_points_list_m[each]
        list_of_vertices = vert_int[each]
        [source_1, dest_1, source_2, dest_2] = list_of_vertices

        edge_int = vertices_dict.keys()[vertices_dict.values().index(intersection_pt)]
        vertex_being_added_1 = vertices_dict.keys()[vertices_dict.values().index(source_1)]
        vertex_being_added_2 = vertices_dict.keys()[vertices_dict.values().index(dest_1)]
        vertex_being_added_3 = vertices_dict.keys()[vertices_dict.values().index(source_2)]
        vertex_being_added_4 = vertices_dict.keys()[vertices_dict.values().index(dest_2)]

        edge1 = "<" + str(edge_int) + "," + str(vertex_being_added_1) + ">"
        edge2 = "<" + str(edge_int) + "," + str(vertex_being_added_2) + ">"
        edge3 = "<" + str(edge_int) + "," + str(vertex_being_added_3) + ">"
        edge4 = "<" + str(edge_int) + "," + str(vertex_being_added_4) + ">"

        e_list = list((edge1, edge2, edge3, edge4))
        edges_final.extend(e_list)
        edge_set = set(edges_final)
        edges_final = list(edge_set)
        unique_v = []


    for z in range(0, len(edges_final)):
        edge_1 = edges_final[z]
        edge_1 = re.sub('<', '(', edge_1)
        edge_1 = re.sub('>', ')', edge_1)
        source_1, dest_1 = ast.literal_eval(edge_1)
        if (source_1 == dest_1):
            delete = "<" + str(source_1) + "," + str(dest_1) + ">"
            edges_repeat_1.append(delete)

        for g in vertices_dict:
            point_1 = vertices_dict[source_1]
            point_2 = vertices_dict[dest_1]

            point_1_x, point_1_y = ast.literal_eval(point_1)
            point_2_x, point_2_y = ast.literal_eval(point_2)
            min_x_of_point = min(point_1_x, point_2_x)
            max_x_of_point = max(point_1_x, point_2_x)
            min_y_of_point = min(point_1_y, point_2_y)
            max_y_of_point = max(point_1_y, point_2_y)
            check_both_points = vertices_dict[g]

            c_x, c_y = ast.literal_eval(check_both_points)
            if ((bool(c_x != min_x_of_point) & bool(c_x != max_x_of_point)) | ((bool(c_y != min_y_of_point) & bool(c_y != max_y_of_point)))):
                if (bool(c_x <= max_x_of_point) & bool(c_x >= min_x_of_point)):
                    if (bool(c_y <= max_y_of_point) & bool(c_y >= min_y_of_point)):
                        if ((round((point_2_y - c_y) * (c_x - point_1_x), 1) == round((point_2_x - c_x) * (c_y - point_1_y), 1)) | (round((c_y - point_1_y) * (point_2_x - point_1_x), 1) == round((point_2_y - point_1_y) * (c_x - point_1_x), 1)) | (round((point_2_y - c_y) * (point_2_x - point_1_x), 1) == round((point_2_y - point_1_y) * (point_2_x - c_x), 1))):
                            del_duplicate = "<" + str(source_1) + "," + str(dest_1) + ">"; edges_repeat_1.append(del_duplicate);
                            edges_repeat_set_1 = set(edges_repeat_1)
                            edges_repeat_1 = list(edges_repeat_set_1)

    for k in range(0, len(edges_repeat_1)):
        edges_final.remove(edges_repeat_1[k])

    for l in range(0, len(edges_final)):
        for l1 in range(l + 1, len(edges_final)):
            edge_1 = edges_final[l]
            edge_1 = re.sub('<', '(', edge_1)
            edge_1 = re.sub('>', ')', edge_1)
            source_1, dest_1 = ast.literal_eval(edge_1)
            edge_2 = edges_final[l1]
            edge_2 = re.sub('<', '(', edge_2)
            edge_2 = re.sub('>', ')', edge_2)
            source_2, dest_2 = ast.literal_eval(edge_2)
            if (source_1 == dest_2 and dest_1 == source_2):
                delete = "<" + str(source_1) + "," + str(dest_1) + ">"
                edges_repeat_2.append(delete)
                edges_repeat_set_2 = set(edges_repeat_2)
                edges_repeat_2 = list(edges_repeat_set_2)

    for m in range(0, len(edges_repeat_2)):
        edges_final.remove(edges_repeat_2[m])

        for d in range(0, len(edges_final)):
            p_r = edges_final[d]
            p_r = re.sub('<', '(', p_r)
            p_r = re.sub('>', ')', p_r)
            x_coord, y_coord = ast.literal_eval(p_r)
            unique_v.append(x_coord)
            unique_s = set(unique_v)
            unique_v = list(unique_s)
            for i in range(0, len(unique_v)):
                for j in range(i + 1, len(unique_v)):
                    edge_bw = "<" + str(unique_v[i]) + "," + str(unique_v[j]) + ">"
                    edges_final.append(edge_bw)
                    graph_set = set(edges_final)
                    edges_final = list(graph_set)


    sys.stdout.write("E {")
    sys.stdout.flush()
    count = len(edges_final)
    for each in edges_final:
        sys.stdout.flush()
        sys.stdout.write(each)
        sys.stdout.flush()
        count = count - 1
        if(count):
            sys.stdout.write(',')
            sys.stdout.flush()
    sys.stdout.write("}" + '\n')
    sys.stdout.flush()


def parse_input1(street_name):
    if all(each.isalpha() or each.isspace() for each in street_name):
        return True
    else:

        return False


def parse_input2(street_name):
    for each in Streets:
        if street_name == each:
            return True
        else:
            return False


def parse_input3(loc):
    empty = True
    pt_list = list()
    i = 0
    while i < len(loc) and empty:
        parse_input_line = loc[i]
        if parse_input_line == "(":
            pt_list.append(parse_input_line)
        elif parse_input_line == ")":
            if len(pt_list) == 0:
                empty = False
            else:
                pt_list.pop()
        i = i + 1
    return empty and len(pt_list) == 0


def parse_input4(st_name):
    if st_name in Streets:
        return False
    else:
        return True


def parse_input5(loc):
    m = re.compile(r'\(-?\d+,-?\d+\)')
    if (m.match(loc)):
        return True
    else:
        return False


def main():
    while True:
        user_input = sys.stdin.readline()
        if (user_input == ''):
            break
        elif (user_input[0] == 'r'):
            user_after_sp = re.split(' +"|"|', user_input)
        else:
            user_after_sp = re.split('" +| +"', user_input)
        if (len(user_after_sp) == 1):
            user_choice = user_after_sp[0]
        elif (len(user_after_sp) == 2):
            user_choice = user_after_sp[0]
            st_name = user_after_sp[1]
            st_name = st_name.lower()
        elif (len(user_after_sp) == 3):
            user_choice = user_after_sp[0]
            st_name = user_after_sp[1]
            st_name = st_name.lower()
            points = user_after_sp[2]
        else:
            error = "Error: Incorrect input Format 6 \n"
            sys.stderr.write(error)
            sys.stdout.flush()
            #flush after every write so that inputis sent right away to a2 and is not stored until the buffer is full.
            continue
        user_choice = user_choice.strip()
        if user_choice == 'a':
            try:
                if (parse_input1(st_name)):
                    if (parse_input3(points)):
                        if (parse_input4(st_name)):
                            points = re.sub(' +', '', points)
                            points = re.sub('\)\(', ') ( ', points)
                            points = re.sub('\( ', '(', points)
                            points = points.split(' ')
                            if all(parse_input5(each) for each in points):
                                Streets[st_name] = points
                            else:
                                sys.stderr.write("Error: Invalid Co-ordinates Input \n")
                                sys.stdout.flush()
                        else:
                            sys.stderr.write("Error: Cannot add a Street that already exists! \n")
                            sys.stdout.flush()
                    else:
                        sys.stderr.write("Error: Incorrect Input Format 1 \n")
                        sys.stdout.flush()
                else:
                    sys.stderr.write("Error: Incorrect Input Format 2\n ")
                    sys.stdout.flush()
            except UnboundLocalError:
                sys.stderr.write("Error: Incomplete Input 3\n ")
                sys.stdout.flush()

        elif user_choice == 'c':
            try:
                if (parse_input2(st_name)):
                    if (parse_input1(st_name)):
                        if (parse_input3(points)):
                            points = re.sub(' +', '', points)
                            points = re.sub('\)\(', ') ( ', points)
                            points = re.sub('\( ', '(', points)
                            points = points.split(' ')
                            if all(parse_input5(each) for each in points):
                                Streets[st_name] = points
                            else:
                                sys.stderr.write("Error: Invalid Co-ordinates Input \n")
                                sys.stdout.flush()
                        else:
                            sys.stderr.write("Error: Invalid Co-ordinates Input \n")
                            sys.stdout.flush()
                    else:
                        sys.stderr.write("Error: Incorrect Input Format 4\n")
                        sys.stdout.flush()
                else:
                    sys.stderr.write("Error: Street does not exist! \n")
                    sys.stdout.flush()
            except UnboundLocalError:
                sys.stderr.write("Error: Incomplete Input \n ")
                sys.stdout.flush()

        elif user_choice == 'r':
            try:
                try:
                    del Streets[st_name]
                except KeyError:
                    sys.stderr.write("Error: Street does not Exist! \n")
                    sys.stdout.flush()
            except UnboundLocalError:
                sys.stderr.write("Error: Incomplete Input \n ")
                sys.stdout.flush()

        elif user_choice == 'g':
            Generate_output()
            sys.stdout.flush()

        else:
            sys.stderr.write("Error: Incorrect Input Format 5!\n")
            sys.stdout.flush()


if __name__ == '__main__':
    main()
