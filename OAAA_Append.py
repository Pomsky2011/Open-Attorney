import struct
import os

def append_asset(binary_path, asset_path):
    # Read the asset file
    with open(asset_path, 'rb') as asset_file:
        asset_data = asset_file.read()

    # Prepare the OAAA header
    asset_name = os.path.basename(asset_path)
    header = struct.pack('!4sI32s', b'OAAA', len(asset_data), asset_name.encode('utf-8'))

    # Append the header and asset data to the binary
    with open(binary_path, 'ab') as binary_file:
        binary_file.write(header)
        binary_file.write(asset_data)

    print(f"Appended {asset_name} to {binary_path}")

if __name__ == "__main__":
    binary_path = "main"  # Replace with your actual binary name
    asset_path = "font.bmp"
    append_asset(binary_path, asset_path)