print(f"jump f0_at_col_0")
for i in range(15):
    print(f"f{i}_to_next_row:")
    print(f"right")
    print(f"border f{i+1}_start_row")
    print(f"move")
    print(f"right")
    print(f"f{i}_to_col_0:")
    print(f"border f{i}_at_col_0")
    print(f"move")
    print(f"jump f{i}_to_col_0")
    print(f"f{i}_at_col_0:")
    print(f"right")
    print(f"f{i}_start_row:")
    print(f"right")

    print(f"f{i}_check_row:")
    for j in range(i):
        print("get")
    print(f"pebble f{i}_continue")
    print(f"jump f{i}_found")
    print(f"f{i}_continue:")
    for j in range(i):
        print("put")
    print(f"border f{i}_to_next_row")
    print(f"move")
    print(f"jump f{i}_check_row")


for i in range(14, 0, -1):
    print(f"f{i}_found:")
    print(f"put")
print("f0_found:")
print("f15_start_row:")
