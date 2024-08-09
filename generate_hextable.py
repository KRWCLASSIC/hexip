import json
import os

def generate_hex_map():
    hex_map = {}
    unicode_value = 0x20
    
    for i in range(256):
        hex_value = f"{i:02X}"
        if unicode_value == 0x7F:
            unicode_value = 0xA1
        elif unicode_value == 0xAD:
            unicode_value += 1
        char = chr(unicode_value)
        if char == '\\':
            char = '\\'
        hex_map[hex_value] = char
        unicode_value += 1
    
    return hex_map

def export_to_json(hex_map, filename):
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(hex_map, f, ensure_ascii=False, indent=2, separators=(',', ': '))
    print(f"Hex map exported to {filename}")

hex_to_char_map = generate_hex_map()

for hex_value, char in hex_to_char_map.items():
    print(f"0x{hex_value}: {repr(char)}")

# Ask user if they want to export to JSON
export_choice = input("\nDo you want to export the hex map to a JSON file? (y/n): ").lower()

if export_choice == 'y':
    filename = "hexlookuptable.json"
    if os.path.exists(filename):
        override_choice = input(f"{filename} already exists. Do you want to overwrite it? (y/n): ").lower()
        if override_choice != 'y':
            print("Export cancelled.")
        else:
            export_to_json(hex_to_char_map, filename)
    else:
        export_to_json(hex_to_char_map, filename)
else:
    print("Export cancelled.")