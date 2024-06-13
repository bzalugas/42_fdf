import sys

def read_ascii_grid(srcname):
    with open(srcname, 'r') as f:
        # Read header
        header = {}
        for _ in range(6):
            line = f.readline().strip()
            key, value = line.split()
            header[key] = float(value)

        # Read data
        data = []
        for line in f:
            data.append([float(value) for value in line.split()])
        return header, data

def write_to_text(data, nodata_value, dstname):
    with open(dstname, 'w') as f:
        for row in data:
            for value in row:
                if value == nodata_value:
                    f.write("0 ")
                else:
                    f.write(f"{int(value)} ")
            f.write("\n")

def arcinfo_grid_to_text(srcname, dstname):
    header, data = read_ascii_grid(srcname)
    nodata_value = header['NODATA_value']
    write_to_text(data, nodata_value, dstname)
    print(f"Conversion completed. Data written to {dstname}")

if len(sys.argv) != 3:
    print("Provide src & dst files")
srcname = sys.argv[1]
dstname = sys.argv[2]
arcinfo_grid_to_text(srcname, dstname)
