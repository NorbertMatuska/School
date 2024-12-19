# Program to generate usernames from a file of users into an output file
# The program checks itself every step of the way
# If anything isn't what It's supposed to be, the program stops without crashing
# It is as robust as it can be
import os
import string
import sys
import getopt


# reads all inputs and writes into output
# not a final output file, just placeholder for joined files
# expects input files to be named input_file[int].txt starting from number 1
def read_and_join_files(input_files, output_file):
    i = len(input_files)
    # while os.path.exists("input_file%s.txt" % i):  #
    #    i += 1

    open(output_file, "w").close()  # if output has some contents, we delete them first, so it does not append

    if i > 1:   # if we have more than one file

        output_file = open(output_file, "a")
        for x in range(i):
            input_file = open(input_files[x], "r")
            data = input_file.read()
            output_file.write(data)  # we write it temporarily into output file
            output_file.write("\n")
            input_file.close()
        output_file.close()

    else:    # if only one input_file is presented
        input_file = open(input_files[i], "r")
        data = input_file.read()
        output_file = open(output_file, "a")
        output_file.write(data)

        output_file.close()
        input_file.close()


# outputs usernames into a file
def output_usernames(list_of_inputs, usernames, output_file):
    tmp = ""
    user_counter = 0
    colon_counter = 0

    open(output_file, "w").close()  # deletes contents of file
    output_file = open(output_file, "a")
    for inputs in list_of_inputs:  # goes through lines of data
        for char in inputs:  # goes through all characters in a line
            tmp += char  # temporary variable to remember the line
            if char == ":" and colon_counter != 1:  # if we come across a colon, we know that the username is supposed
                tmp += usernames[user_counter]      # to go after the first colon
                tmp += ":"                          # I could also use .append() instead of user_counter, but I like
                user_counter += 1                   # this better
                colon_counter += 1
        tmp += "\n"
        output_file.write(tmp)
        tmp = ""
        colon_counter = 0
    output_file.close()


# generates usernames that we wrote into output_file
def generate_usernames(output_file):
    with open(output_file, "r") as file:
        list_of_inputs = file.read().splitlines()  # gets the list of users and deletes newlines
        file.close()

    usernames = []
    count_colons = 0
    tmp = ""
    number_for_user = 1

    for inputs in list_of_inputs:  # goes line by line
        for char in inputs:  # goes through characters in a line
            if char == ":":  # we get to the first colon, count it, and continue to the next character
                count_colons += 1
                continue
            if len(tmp) == 8:
                break
            elif count_colons == 1 and len(tmp) != 1:  # we store the first character of users first name
                tmp += char.lower()
            elif count_colons == 2 and len(tmp) != 2:  # we store the first character of users middle name
                tmp += char.lower()  # if the user has no middle name, it doesn't matter, we have the colon_counter
            elif count_colons == 3:  # and there will always be the same number of colons
                tmp += char.lower()

        for identity_check in usernames:    # we check if the username already exists
            if tmp == identity_check:
                tmp += str(number_for_user)  # if it does, we add a number behind it
                number_for_user += 1
        usernames.append(tmp)
        tmp = ""
        count_colons = 0
    output_usernames(list_of_inputs, usernames, output_file)


def check_files(input_files, output_file):
    if len(input_files) == 0 or output_file == "":  # checks if we received any files
        print("There are no input files or there is no output file")
        sys.exit(0)
    # I could make a list of all human-readable file extensions, but for the sake of simplicity, we will use only .txt
    elif not output_file.endswith(".txt"):
        print("The output file does not seem to be a .txt file")
        print("If you want to read the results of this program, try again")
        sys.exit(0)
    else:
        for file in input_files:
            # Let's keep it simple; we cannot let user write into a .exe file for example
            if not file.endswith(".txt"):
                print("One or more input files does not seem to be a .txt file")
                print("Please try again")
                sys.exit(0)
        for file in input_files:
            if not os.path.isfile(file):  # we check if the file we are trying to open exists
                print(file + " does not seem to exist in this directory")
                sys.exit(0)
            with open(file, "r") as check_contents:  # check for the contents of input files
                if os.path.getsize(file) != 0:  # we don't need to check empty files
                    data = check_contents.read().splitlines()
                    count_colons = 0
                    for lines in data:
                        count_colons += lines.count(":")  # we count the colons, because there will always be 4 colons
                        if not lines.startswith(tuple(string.digits)):  # we do a check if the user has some ID
                            print("-|" + lines + "|- does not have an ID")
                            print("or the ID is not in correct position in file: " + file)
                            print("Please correct this mistake")
                            sys.exit(0)
                    if count_colons / len(data) != 4:  # check the colons; there should be 4
                        print("The data in input file: " + file + " does not seem to be correctly formatted")
                        print("Data should look like so: ID(num):First_Name:Middle_Name:Last_Name:Occupation")
                        sys.exit(0)
                check_contents.close()
        print("Input files: -|", input_files, "|- exist.")
        print("All files end with .txt")
        print("Data in input files seems to be in correct format")
        print("Generating usernames")
        print("\n")


def main(argv):
    output_file = ""

    try:
        opts, args = getopt.getopt(argv, "hi:o:", ["input_file=", "output_file="])
    except getopt.GetoptError:
        print("ugen.py -o <output_file> <input_file>...")
        sys.exit(2)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print("ugen.py -o <output_file> <input_file>")
            sys.exit(0)
        elif opt in ("-o", "--output"):
            output_file = arg
    if output_file == "":
        print("Please provide an output file")
        sys.exit(0)
    input_files = args

    check_files(input_files, output_file)  # we check the files first
    read_and_join_files(input_files, output_file)
    generate_usernames(output_file)


if __name__ == "__main__":
    main(sys.argv[1:])
