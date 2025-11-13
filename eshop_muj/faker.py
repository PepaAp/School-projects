from faker import Faker
import random
from datetime import datetime, timedelta

fake = Faker("cs_CZ")
random.seed(42)

# Počet záznamů
NUM_USERS = 500
NUM_ORDERS = 750
NUM_ORDER_ITEMS = 1500

# Funkce pro náhodné datum posledního roku s různými časy během dne
def random_date():
    start = datetime.now() - timedelta(days=365)
    end = datetime.now()
    date = fake.date_between(start_date=start, end_date=end)
    # Různé hodiny během dne (ráno, poledne, odpoledne, večer, noc)
    hour = random.choice([7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23])
    minute = random.randint(0, 59)
    second = random.randint(0, 59)
    return f"{date.strftime('%Y-%m-%d')} {hour:02d}:{minute:02d}:{second:02d}"

# Vymazání tabulek
truncate_tables = [
    "`order_item`", "`order`", "`inventory`", "`product`", "`category`", "`list_of_categories`", "`user`"
]

sql_lines = []
# Vypnutí kontroly cizích klíčů
sql_lines.append("SET FOREIGN_KEY_CHECKS = 0;")
sql_lines.append("")

for table in truncate_tables:
    sql_lines.append(f"TRUNCATE TABLE {table};")

# Zapnutí kontroly cizích klíčů
sql_lines.append("")
sql_lines.append("SET FOREIGN_KEY_CHECKS = 1;")
sql_lines.append("")

# ---------------- Users (rodiny na stejných adresách) ----------------
users = []
# Vytvoříme rodiny - cca 167 adres, na každé 3 lidé = 500+ uživatelů
addresses = []
num_families = NUM_USERS // 3
for _ in range(num_families):
    street = f"{fake.street_name()} {random.randint(1, 150)}"
    city = fake.city()
    postal = fake.postcode()
    addr = f"{street}, {postal} {city}"
    addresses.append(addr)

user_id = 1
for addr in addresses:
    # Na každé adrese 3 lidé (rodina)
    family_surname = fake.last_name()
    for _ in range(3):
        if user_id > NUM_USERS:
            break
        first_name = fake.first_name()
        email = f"{first_name.lower()}.{family_surname.lower()}{random.randint(1,999)}@email.cz"
        phone = fake.phone_number()
        users.append((user_id, first_name, family_surname, email, addr, phone))
        user_id += 1
    if user_id > NUM_USERS:
        break
    
# ---------------- List of Categories (hlavní kategorie) ----------------
list_of_categories = [
    (1, "Elektronika"),
    (2, "Oblečení a móda"),
    (3, "Domácnost"),
    (4, "Sport a outdoor"),
    (5, "Knihy a média")
]

# ---------------- Categories (podkategorie) ----------------
categories_data = {
    1: ["Mobilní telefony", "Notebooky", "Televize", "Sluchátka"],
    2: ["Pánské oblečení", "Dámské oblečení", "Obuv", "Doplňky"],
    3: ["Nábytek", "Kuchyňské potřeby", "Dekorace", "Zahrada"],
    4: ["Fitness", "Cyklistika", "Běh", "Kempování"],
    5: ["Beletrie", "Odborná literatura", "Časopisy", "E-knihy"]
}

categories = []
cat_id = 1
for list_id, cat_names in categories_data.items():
    for cat_name in cat_names:
        categories.append((cat_id, list_id, cat_name))
        cat_id += 1

# ---------------- Products (reálné produkty s reálnými cenami) ----------------
products_by_category = {
    "Mobilní telefony": [
        ("iPhone 15 Pro", 32990), ("Samsung Galaxy S24", 27990), ("Google Pixel 8", 21990),
        ("Xiaomi 14", 18990), ("OnePlus 12", 23990)
    ],
    "Notebooky": [
        ("Dell XPS 13", 34990), ("Lenovo ThinkPad X1", 42990), ("MacBook Air M2", 38990),
        ("HP Pavilion 15", 19990), ("ASUS ZenBook", 28990)
    ],
    "Televize": [
        ("Samsung QE55Q80C 55\"", 24990), ("LG OLED 48\"", 32990), ("Sony Bravia 65\"", 45990),
        ("Philips 43PUS8008", 12990)
    ],
    "Sluchátka": [
        ("Sony WH-1000XM5", 8990), ("AirPods Pro 2", 6990), ("Bose QuietComfort", 7990),
        ("JBL Tune 510BT", 990), ("Sennheiser HD 450BT", 3490)
    ],
    "Pánské oblečení": [
        ("Pánská košile", 890), ("Pánské jeans", 1290), ("Pánský svetr", 1490),
        ("Pánská bunda", 2990), ("Pánské tričko", 490)
    ],
    "Dámské oblečení": [
        ("Dámské šaty", 1590), ("Dámská halenka", 790), ("Dámské kalhoty", 1190),
        ("Dámský kabát", 3490), ("Dámská sukně", 890)
    ],
    "Obuv": [
        ("Nike Air Max", 3290), ("Adidas Ultraboost", 3990), ("Converse Chuck Taylor", 1790),
        ("Puma Suede", 2290), ("Vans Old Skool", 1990)
    ],
    "Doplňky": [
        ("Kožená peněženka", 690), ("Hodinky Casio", 1490), ("Batoh", 890),
        ("Slunční brýle", 590), ("Kabelka", 1290)
    ],
    "Nábytek": [
        ("Konferenční stolek", 3990), ("Knihovna", 4990), ("Křeslo", 5990),
        ("Postel 180x200", 12990), ("Skříň", 8990)
    ],
    "Kuchyňské potřeby": [
        ("Mixér Bosch", 2490), ("Pánev Tefal", 890), ("Sada hrnců", 1990),
        ("Kávovar DeLonghi", 4990), ("Varná konvice", 790)
    ],
    "Dekorace": [
        ("Obrazy na zeď", 590), ("Květináč", 290), ("Svíčky", 190),
        ("Váza", 390), ("Koberec 120x170", 1990)
    ],
    "Zahrada": [
        ("Sekačka na trávu", 8990), ("Zahradní nůžky", 490), ("Gril Weber", 12990),
        ("Zahradní set", 6990), ("Slunečník", 1990)
    ],
    "Fitness": [
        ("Činky 2x5kg", 890), ("Fitness podložka", 490), ("Expandér", 290),
        ("Kettlebell 8kg", 590), ("Fitbox", 12990)
    ],
    "Cyklistika": [
        ("Horské kolo Trek", 18990), ("Cyklistická helma", 890), ("Cyklo rukavice", 390),
        ("Cyklo dres", 690), ("Cyklo světlo", 490)
    ],
    "Běh": [
        ("Běžecké boty Asics", 2990), ("Běžecká čelenka", 190), ("Běžecké kalhoty", 890),
        ("GPS hodinky Garmin", 7990), ("Běžecká bunda", 1990)
    ],
    "Kempování": [
        ("Stan 3 osoby", 3990), ("Spacák", 1490), ("Karimatka", 690),
        ("Plynový vařič", 890), ("Turistický batoh 50L", 2490)
    ],
    "Beletrie": [
        ("Hobit - J.R.R. Tolkien", 349), ("1984 - George Orwell", 299), ("Harry Potter", 399),
        ("Malý princ", 249), ("Stopařův průvodce", 329)
    ],
    "Odborná literatura": [
        ("Python pro začátečníky", 499), ("Čistý kód", 599), ("Ekonomie 21. století", 699),
        ("Marketing v praxi", 549), ("Návrhové vzory", 649)
    ],
    "Časopisy": [
        ("National Geographic CZ", 89), ("PC World", 59), ("Elle", 79),
        ("Auto Motor Sport", 69), ("Forbes", 99)
    ],
    "E-knihy": [
        ("Sapiens - Yuval Harari (e-book)", 299), ("Atomové návyky (e-book)", 249),
        ("Myšlení rychlé a pomalé (e-book)", 349), ("Rich Dad Poor Dad (e-book)", 199)
    ]
}

products = []
prod_id = 1
for cat_tuple in categories:
    cat_id_val, list_id_val, cat_name = cat_tuple
    if cat_name in products_by_category:
        for prod_name, prod_price in products_by_category[cat_name]:
            products.append((prod_id, cat_id_val, prod_name, prod_price))
            prod_id += 1

# ---------------- Orders (více objednávek od stejných uživatelů) ----------------
orders = []
payment_methods = ["card", "cash", "paypal", "klarna"]
statuses = ["created","payed","packaging","shipped","in_transit","delivery","delivered"]

# Vytvoříme 750 objednávek rovnoměrně mezi uživatele
order_id = 1
order_totals = {}  # Slovník pro sledování celkových cen objednávek
for _ in range(NUM_ORDERS):
    user = random.choice(users)  # Náhodný uživatel
    date = random_date()
    
    # Určíme stav podle stáří objednávky
    order_date = datetime.strptime(date, '%Y-%m-%d %H:%M:%S')
    days_ago = (datetime.now() - order_date).days
    
    # Objednávky starší než 14 dní jsou doručené
    # Objednávky 7-14 dní jsou ve fázi dopravy/doručování
    # Novější objednávky mají různé stavy
    if days_ago > 14:
        status = "delivered"
    elif days_ago > 7:
        status = random.choice(["shipped", "in_transit", "delivery", "delivered"])
    elif days_ago > 3:
        status = random.choice(["payed", "packaging", "shipped"])
    else:
        status = random.choice(["created", "payed", "packaging"])
    
    orders.append((order_id, user[0], date, 0, user[4], random.choice(payment_methods), status))
    order_totals[order_id] = 0
    order_id += 1

# ---------------- Order Items (více produktů v objednávkách) ----------------
order_items = []
item_id = 1
for order in orders:
    order_id_val = order[0]
    # Každá objednávka bude mít 1-4 produkty
    num_items = random.randint(1, 4)
    for _ in range(num_items):
        product = random.choice(products)
        quantity = random.randint(1, 3)
        price = round(product[3] * quantity, 2)
        order_items.append((item_id, order_id_val, product[0], quantity, price))
        order_totals[order_id_val] += price
        item_id += 1

# Aktualizace celkových cen objednávek
orders = [(o[0], o[1], o[2], order_totals[o[0]], o[4], o[5], o[6]) for o in orders]

# ---------------- SQL Insert Helper ----------------
def insert_lines(table, columns, values_list):
    sql_lines.append(f"-- {table}")
    for values in values_list:
        val_str = ", ".join(f"'{v}'" if isinstance(v, str) else str(v) for v in values)
        sql_lines.append(f"INSERT INTO `{table}` ({', '.join(columns)}) VALUES ({val_str});")
    sql_lines.append("")

# ---------------- Vkládání dat ----------------
insert_lines("user", ["id_user","surname","lastname","email","address","phone"], users)
insert_lines("list_of_categories", ["id_list_of_categories","name"], list_of_categories)
insert_lines("category", ["id_category","list_of_categories_id","name"], categories)
insert_lines("product", ["id_product","category_id","name","price"], products)
insert_lines("order", ["id_order","user_id","date","total_price","address","payment_method","status"], orders)
insert_lines("order_item", ["id_order_item","order_id","product_id","quantity","price"], order_items)

# Uložení do SQL souboru
sql_dump_path = "realistic_eshop_data.sql"
with open(sql_dump_path, "w", encoding="utf-8") as f:
    f.write("\n".join(sql_lines))

print(f"SQL dump uložen do: {sql_dump_path}")
