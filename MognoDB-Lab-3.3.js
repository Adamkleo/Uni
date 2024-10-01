
/*
Provider has a CIF String which is its key
Name, unique Email, address
It offers products, o to many where each product has:
An ID, name, address, size list where sizes range from XS -> XXXL
*/


// First insertion

db.productos.insertOne({
    "nombre": "Camiseta chula",
    "precio": 36,
    "tallas": ["L", "XL"],
    "proveedor": {
        "CIF": "B56674409",
        "nombre": "Camifab"
    },
    "total": 5656
});

db.productos.insertMany([
    {
        "precio": "8,35€",
        "tallas": ["S", "XS"],
        "proveedor": {
            "CIF": "B56674409",
            "nombre": "Camifab"
        }
    },
    {
        "nombre": "Falda elegante",
        "tallas": [40],
        "proveedor": {
            "nombre": "Shurimi"
        }
    }
]);



// Next, we create a list of products, ordering them by price in descending order. 
// Write the query and explain what happens:

db.productos.find().sort({ "precio": -1 });

// Some products dont have price, others not have a name, we need validation here


db.runCommand({
    collMod: "productos",
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["nombre", "precio", "tallas"],
            properties: {
                nombre: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                precio: {
                    bsonType: "number",
                    description: "must be a number and is required"
                },
                tallas: {
                    bsonType: "array",
                    items: {
                        bsonType: "string",
                        enum: ["XS", "S", "M", "L", "XL", "XXL", "XXXL"],
                        description: "must be one of the allowed values: XS, S, M, L, XL, XXL, XXXL"
                    },
                    description: "must be an array of allowed sizes and is required"
                },
                proveedor: {
                    bsonType: "object",
                    required: ["CIF", "nombre"],
                    properties: {
                        CIF: {
                            bsonType: "string",
                            description: "CIF must be a string"
                        },
                        nombre: {
                            bsonType: "string",
                            description: "must be a string and is required"
                        }
                    },
                    description: "must be an object with 'nombre' required"
                },
                total: {
                    bsonType: "number",
                    description: "must be a number if present"
                }
            }
        }
    }
});



// Now when inserting:

db.productos.insertOne(
    {
        "precio": "8,35€",
        "tallas": ["S", "XS"],
        "proveedor": {
            "CIF": "B56674409",
            "nombre": "Camifab"
        }
    }
)

// We get a validation error

db.getCollectionInfos({ name: "productos" })[0].options.validator


db.productos.insertOne(
    {
        "nombre": "kilot",
        "precio": 27,
        "tallas": ["S", "XS"],
        "proveedor": {
            "CIF": "B56674409",
            "nombre": "Camifab"
        }
    }
)

// Works!

db.productos.insertOne(
    {
        "nombre": "boxer",
        "precio": -100,
        "tallas": ["S", "XS"],
        "proveedor": {
            "CIF": "B56674409",
            "nombre": "Camifab"
        }
    }
)

// Also works, this is bad, should only accept positives


db.runCommand({
    collMod: "productos",
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["nombre", "precio", "tallas"],
            properties: {
                nombre: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                precio: {
                    bsonType: "number",
                    minimum: 0,
                    description: "must be a positive number and is required"
                },
                tallas: {
                    bsonType: "array",
                    items: {
                        bsonType: "string",
                        enum: ["XS", "S", "M", "L", "XL", "XXL", "XXXL"],
                        description: "must be one of the allowed values: XS, S, M, L, XL, XXL, XXXL"
                    },
                    description: "must be an array of allowed sizes and is required"
                },
                proveedor: {
                    bsonType: "object",
                    required: ["nombre"],
                    properties: {
                        CIF: {
                            bsonType: "string",
                            description: "CIF must be a string"
                        },
                        nombre: {
                            bsonType: "string",
                            description: "must be a string and is required"
                        }
                    },
                    description: "must be an object with 'nombre' required"
                },
                total: {
                    bsonType: "number",
                    description: "must be a number if present"
                }
            }
        }
    }
});




db.productos.insertOne(
    {
        nombre: 'Test product',
        precio: 100,
        tallas: ['XL']
    }
)




// Part 2:

db.proveedores.insertOne(
    {
        CIF: 'B56674409',
        nombre: 'Camifab',
        dir: 'Avda. del comercio s/n',
        email: 'info@camifab.es',
        responsable: 'Felipe Sastre'
    }
)


db.runCommand({
    collMod: "proveedores",
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["CIF", "email"],
            properties: {
                CIF: {
                    bsonType: "string",
                    pattern: "^[A-Z][0-9]{8}$",
                    description: "must be an uppercase letter followed by 8 numbers"
                },
                nombre: {
                    bsonType: "string",
                    description: "must be a string"
                },
                dir: {
                    bsonType: "string",
                    description: "must be a string"
                },
                email: {
                    bsonType: "string",
                    pattern: "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$",
                    description: "must be an email"
                },
                responsable: {
                    bsonType: "string",
                    description: "must be a string"
                }
            }
        }
    }
});


db.proveedores.insertOne(
    {
        CIF: 'B56674409',
        nombre: 'Camifab',
        dir: 'Avda. del comercio s/n',
        email: 'info@camifab.es',
        responsable: 'Felipe Sastre'
    }
)





db.runCommand({
    collMod: "productos",
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["nombre", "precio", "tallas"],
            properties: {
                nombre: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                precio: {
                    bsonType: "number",
                    minimum: 0,
                    description: "must be a positive number and is required"
                },
                tallas: {
                    bsonType: "array",
                    items: {
                        bsonType: "string",
                        enum: ["XS", "S", "M", "L", "XL", "XXL", "XXXL"],
                        description: "must be one of the allowed values: XS, S, M, L, XL, XXL, XXXL"
                    },
                    description: "must be an array of allowed sizes and is required"
                },
                proveedor: {
                    bsonType: "object",
                    required: ["nombre"],
                    properties: {
                        CIF: {
                            bsonType: "string",
                            description: "CIF must be a string"
                        },
                        nombre: {
                            bsonType: "string",
                            description: "must be a string and is required"
                        }
                    },
                    description: "must be an object with 'nombre' required"
                },
                total: {
                    bsonType: "number",
                    description: "must be a number if present"
                }
            }
        }
    }
});