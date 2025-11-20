<h1>Databáze pro jednoduchý e-shop</h1>

<p>
Tento projekt obsahuje návrh databáze pro jednoduchý e-shop. Umožňuje spravovat
produkty, skladové zásoby, uživatele, objednávky a jejich položky.
</p>

<h2>ER diagram</h2>

<p>
  <img src="https://github.com/PepaAp/School-projects/blob/main/eshop_muj/eshop-dia.svg" alt="ER diagram">
</p>

<h2>Popis databázových prvků</h2>

<dl>
  <dt><strong>Produkty a inventář</strong></dt>
  <dd>Správa produktů, jejich cen, kategorií a skladových zásob.</dd>

  <dt><strong>Uživatelé</strong></dt>
  <dd>Evidence zákazníků včetně kontaktních údajů a historie objednávek.</dd>

  <dt><strong>Objednávky</strong></dt>
  <dd>Objednávky obsahují položky, stav objednávky a typ platby.</dd>

  <dt><strong>Vazby</strong></dt>
  <dd>Databáze je propojena pomocí cizích klíčů pro snadné dotazování.</dd>
</dl>

<h2>📄 DBML definice</h2>

<pre><code>Enum payment_enum {
  card
  cash
  paypal
  klarna
}

Enum status_enum {
  created
  payed
  packaging
  shipped
  in_transit
  delivery
  delivered
}

Table inventory {
  id_inventory integer [primary key, increment]
  product_id integer [not null]
  quantity integer
}

Table list_of_categories {
  id_list_of_categories integer [primary key, increment]
  name varchar(20)
}

Table category {
  id_category integer [primary key, increment]
  list_of_categories_id integer [not null]
  name varchar(20)
}

Table product {
  id_product integer [primary key, increment]
  category_id integer [not null]
  name varchar(50)
  price decimal(10,2)
}

Table user {
  id_user integer [primary key, increment]
  surname varchar(25)
  lastname varchar(25)
  email varchar(30) [unique, not null]
  address varchar(100)
  phone varchar(15)
  photo blob
}

Table order {
  id_order integer [primary key, increment]
  user_id integer [not null]
  date timestamp
  total_price decimal(10,2)
  address varchar(100)
  payment_method payment_enum
  status status_enum
}

Table order_item {
  id_order_item integer [primary key, increment]
  order_id integer [not null]
  product_id integer [not null]
  quantity integer
  price decimal(10,2)
}

Ref: inventory.product_id > product.id_product
Ref: category.list_of_categories_id > list_of_categories.id_list_of_categories
Ref: product.category_id > category.id_category
Ref: order.user_id > user.id_user
Ref: order_item.order_id > order.id_order
Ref: order_item.product_id > product.id_product
</code></pre>
