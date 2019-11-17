class ArraySubSet:

    # initialise private variables (its like construct and private in C++)
    def __init__(self, Array1, Array2, SubSet=True):
        self.Array1 = Array1
        self.Array2 = Array2
        self.SubSet = SubSet

    # map will iterate the input function,
    # strip and split will remove spaces,
    # `list` will create a list that includes iterated inputs
    def GetArrays(self):
        print("write the elements of the set with spaces")
        self.Array1 = list(map(int, input("Array1: ").strip().split()))
        self.Array2 = list(map(int, input("Array2: ").strip().split()))

    # check for every element in Array2, if its not exist in Array1, set SubSet to False
    def CheckSubSet(self):
        for i in self.Array2:
            if i not in self.Array1:
                self.SubSet = False

        # if SubSet is False, then print...
        if not self.SubSet:
            print("Array2 is NOT a subset!\n")

        # if SubSet is True, print...
        else:
            print("Array2 is a subset\n")


while True:
    # initialise class with empty arrays
    Set = ArraySubSet([], [])

    # use the class functions
    Set.GetArrays()
    Set.CheckSubSet()

    print("===========================================================================================================")
