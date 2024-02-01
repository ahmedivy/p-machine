with open("output.txt", "r") as f:
    lines = f.readlines()

with open("FactorialOutput.txt", "r") as f:
    lines2 = f.readlines()

for i in range(len(lines)):
    assert lines[i].strip() == lines2[i].strip(), f"Test failed at line {i+1}"

print("Test passed")
        