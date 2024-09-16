import json
import os

def generate_hex_map():
    hex_map = {}
    unicode_value = 0x20
    
    for i in range(256):
        hex_value = f"{i:02X}"
        if unicode_value == 0x7F:
            unicode_value = 0xA1  # Skip DEL and start from 0xA1
        elif unicode_value == 0xAD:
            unicode_value += 1  # Skip soft hyphen and continue
        char = chr(unicode_value)
        if char == '\\':
            char = '\\'  # Escape backslashes if necessary
        hex_map[hex_value] = char
        unicode_value += 1
    
    return hex_map

def generate_reversed_hex_map(hex_map):
    reversed_map = {v: k for k, v in hex_map.items()}
    return reversed_map

def export_to_json(data, filename):
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=2, separators=(',', ': '))
    print(f"Data exported to {filename}")

# Generate hex-to-character map
hex_to_char_map = generate_hex_map()

# Generate character-to-hex map
char_to_hex_map = generate_reversed_hex_map(hex_to_char_map)

# Print hex-to-character and character-to-hex mapping
for hex_value, char in hex_to_char_map.items():
    print(f"0x{hex_value}: {repr(char)}")
for char, hex_value in char_to_hex_map.items():
    print(f"Char {repr(char)}: 0x{hex_value}")

# Ask user if they want to export the hex maps to JSON files
export_choice = input("\nDo you want to export the hex maps to JSON files? (y/n): ").lower()

if export_choice == 'y':
    hex_filename = "hexlookuptable.json"
    reversed_filename = "reversed_hexlookuptable.json"
    
    if os.path.exists(hex_filename):
        override_choice = input(f"{hex_filename} already exists. Do you want to overwrite it? (y/n): ").lower()
        if override_choice != 'y':
            print("Export cancelled.")
        else:
            export_to_json(hex_to_char_map, hex_filename)
    else:
        export_to_json(hex_to_char_map, hex_filename)
    
    if os.path.exists(reversed_filename):
        override_choice = input(f"{reversed_filename} already exists. Do you want to overwrite it? (y/n): ").lower()
        if override_choice != 'y':
            print("Export cancelled.")
        else:
            export_to_json(char_to_hex_map, reversed_filename)
    else:
        export_to_json(char_to_hex_map, reversed_filename)
else:
    print("Export cancelled.")
