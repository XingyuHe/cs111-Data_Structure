"""

FILE:           pizzas.py

AUTHOR:         Xingyu He

DATE:           Jan 19 2018 

DESCRIPTION:    This program simulates a pizza party. You can order
                , eat, and consolidate pizzas.

"""

import random

# You may find it useful to have a Pizza class.  Please feel free to
# add to this class as you see fit.

class Pizza(object):
    """This is a class of pizza. """

    def __init__(self, kind, slices = 8):
        """constructor for the Pizza class."""

        self._kind = kind
        self._slices = slices

    def __str__(self):
        """The output of the object."""

        return self._kind + '(' + str(self._slices) + ')'

    def get_slices(self):
        """Return the slices that this pizza has. """

        return self._slices


        
class PizzaTable(object):
    """This is a class of pizza table that can represent a table of Pizzas."""

    def __init__(self, n, m, kinds):
        """ construct a pizza table with n rows and m columns.  Order and 
            place n*m pizzas in row-major order, alternating kinds.  For
            example,
            PizzaTable(3, 4, ["pepperoni", "pepperoni", "plain",
                              "sausage", "buffalo"]) 
            would build:
+--------------+--------------+--------------+--------------+
| pepperoni(8) | pepperoni(8) | plain(8)     | sausage(8)   |
+--------------+--------------+--------------+--------------+
| buffalo(8)   | pepperoni(8) | pepperoni(8) | plain(8)     |
+--------------+--------------+--------------+--------------+
| sausage(8)   | buffalo(8)   | pepperoni(8) | pepperoni(8) |
+--------------+--------------+--------------+--------------+

        @PRE: n and m are integers, both greater than 0.
              kinds is a list of strings, whose length is at least 1.

"""
        # make sure that the parameters are of the correct type and length. 
        assert(type(kinds) == list and len(kinds) > 0)
        assert(all(isinstance(x, str) for x in kinds))

        # initialize attributes
        self._row = n
        self._col = m
        self._kinds = kinds
        self._table = []

        # construct self._table
        i = 0

        for row in range(n):
            single_row = []

            for col in range(m):

                # use mod to go through the list of pizza over and over again. 
                # i represent the number of the pizza created. 
                pizza = Pizza(self._kinds[i % len(self._kinds)])
                single_row.append(pizza)
                i += 1

            self._table.append(single_row)

	# FINISH THIS METHOD

    # This method is provided for you
    def print(self):
        """ Write this table to the screen in a simple format. """

        for row in range(len(self._table)):
            for col in range(len(self._table[row])):
                print(self._table[row][col], end=" ")
            print()

    def find_cells_with(self, kind):
        """ return a list of tuples: locations on this table containing at 
            least one slice of pizza of the given kind. """
	# FINISH THIS METHOD

        lst = []

        for row in range(len(self._table)):

            for column in range(len(self._table[row])):

                # check the kind of the pizza at that position.
                if self._table[row][column]._kind == kind:

                    # make sure that there is pizza at that position. 
                    if self._table[row][column]._slices > 0:
                        lst.append((row,column))

        return lst

    def take_slice(self, position):
        """ Remove a slice of pizza from the table at the given position.

        @PRE: position is a tuple (row, col) with a valid row and col. """

        row, col = position
        assert 0 <= row < len(self._table)
        assert 0 <= col < len(self._table[row])
        assert self._table[row][col].get_slices() > 0

        self._table[row][col]._slices -= 1 

	# FINISH THIS METHOD

    def consolidate(self):
        """ Rearrange pizzas on the table so that slices of the same kind are 
            together, favoring positions in row major order. """
	# FINISH THIS METHOD
        
        # kind_lst contains the pizzas separed by kinds. 
        kind_lst = []

        # row represent the kind of pizza.
        for i in self._kinds:
            kind_lst.append([])

        # fill the kind_lst with pizzas. 
        for row in self._table:

            for pizza in row:

                # This for loop check the kind of pizza it is. 
                for kind in self._kinds:

                    # This if statement matches the right kind of pizza and 
                    # put it in that right row of kind_lst.
                    if pizza._kind == kind:
                        kind_index = self._kinds.index(kind)
                        kind_lst[kind_index].append(pizza)

        # find the total amount of pizzas in each kind and redistribute them in 
        # row order. 
        for kind in kind_lst:

            total_slices = 0

            # find the total slices.
            for pizza in kind:

                slices = pizza.get_slices()
                total_slices += slices

            # redistrbute the slices. 
            for pizza in kind:

                # if total slices are more than 8, add 8 slices to this pizza.
                if total_slices > 8:
                    pizza._slices = 8
                    total_slices -= 8

                # if total slices is less or equal to 8 and bigger than 0, 
                # this pizza would be contain the leftover slices. 
                elif total_slices > 0:
                    pizza._slices = total_slices
                    total_slices -= total_slices

                # If total slices are run out, there will be no slice on this 
                # pizza. 
                else:
                    pizza._slices = 0


    def get_kind(self, position):
        """ return the kind of pizza that is, or is supposed to be, 
        in the cell at the given position 

        @PRE: position is a tuple (row, col) with a valid row and col. """
	# FINISH THIS METHOD (with proper assert statements as well.)

        row = position[0]
        col = position[1]

        # Make sure that the position could be found on the table.
        assert 0 <= row < self._row
        assert 0 <= col < self._col

        return self._table[row][col]._kind

    def order(self, position, kind):
        """ Put a new pizza on the table.
        @PRE: position is a tuple (row, col) with a valid row and col;
              kind is a string matching the kind of pizza that 
                  belongs at position; and
              There are no pizza slices at position. """
	# FINISH THIS METHOD (with proper assert statements as well.)

        existed_kind = self.get_kind(position)

        row = position[0]
        col = position[1]
        
        # make sure that the existed kind is the same kind ordered. 
        assert existed_kind == kind
        assert self._table[row][col]._slices == 0

        self._table[row][col]._slices = 8

    def get_slices(self, position):
        """ Return the number of slices at a particular position.
        @PRE: position is a tuple (row, col) with a valid row and col """
	# FINISH THIS METHOD (with proper assert statements as well.)

        row = position[0]
        col = position[1]

        # make sure that the position can be found in the table.
        assert 0 <= row < self._row
        assert 0 <= col < self._col

        return self._table[row][col]._slices

    def pprint(self):
        """ Write this table to the screen in a format like the examples.  The 
            width of each cell is the same, exactly the size to accommodate 
            the longest pizza kind. """
	# FINISH THIS METHOD
        
        # find the maximum length of the pizza kinds
        longest_pizza_kind = 0

        for kind in self._kinds:
            # This for loop goes through every single kind. 
            # longest_pizza_kind will have the value of the longest length. 
            if len(kind) > longest_pizza_kind:

                longest_pizza_kind = len(kind)
        
        # print the table.

        # each row of table is consisted of two lines. Line_1s on the top will 
        # be the top edge of each row. Line 2 will be knd of pizza displayed and 
        # and the side edges of the cell. 
        for row in range(self._row):
            line_1s = ''
            line_2s = ''

            for cell in range(self._col):
                # Here, line_1 represents the top edge of each cell. 
                # line_2 represents the content displayed on each cell and the 
                # side edges. The length of the cell is determined by the length
                # of the longest pizza kind. 

                line_1 = '+' + '-' * (longest_pizza_kind + 5)
                line_2 = '| %s'% self._table[row][cell]
                # if the length of line_2 is not the longest, space will be used
                # to make sure that the length of cell is consistent with the 
                # longest cell. 
                line_2 += (longest_pizza_kind + 6 - len(line_2)) * ' '

                # This if statement is used to determine wether the cell is the 
                # last cell of the row. If it is, '+' is added on line_1 and 
                # '|' is added on line_2 to complete the row. 
                if cell == self._col - 1:
                    line_1 += '+'
                    line_2 += '|'

                # connect all the line_1 and line_2.
                line_1s += line_1
                line_2s += line_2

            # when one row is completed, it is then printed. 
            print(line_1s)
            print(line_2s)

        # print one more line of line_1 to complete the table, since edges of 
        # rows are all the same. 
        print(line_1s)

        
def main():
    """ Here is a sample program for testing your implementation. """

    N = 5
    M = 2
    types = ["Pepperon", "Plain", "Sausage"]
    pt = PizzaTable(N, M, types)
    cells = pt.find_cells_with('Sausage')

    for i in range(1000):
        print(i)
        pt.print()
        v = random.randrange(20)

        if v == 0:
            print("CONSOLIDATE!")
            pt.consolidate()
        elif v < 5:
            cell = (random.randrange(N), random.randrange(M))
            if pt.get_slices(cell) == 0:
                print("ORDERING!!")
                pt.order(cell, pt.get_kind(cell))
        else:
            got_some = False
            preference = types[:]
            random.shuffle(preference)
            for t in preference:
                cells = pt.find_cells_with(t)
                print(cells)
                if len(cells) > 0:
                    print(t)
                    cell = random.choice(cells)
                    pt.take_slice(cell)
                    got_some = True
                    break
            if not got_some:
                print("WE'RE OUT OF PIZZA")
    print()
    pt.print()

if __name__ == "__main__":
    main()
