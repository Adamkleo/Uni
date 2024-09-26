/*
This file contains the exercises of the MongoDB Lab
*/


// 2.1 - Recover the minimum value of the field 'pop' for all cities.
db.zips.aggregate([
  {
    $group: {
      _id: "$city",
      minPopulation: { $min: "$pop" }
    }
  }
])



// 2.2 - Retrieve all the zip codes in the city "Springfield". How many?
db.zips.aggregate([
  { $match: { city: "SPRINGFIELD" } },
  { $project: { _id: 1 } }
])
db.zips.countDocuments({ city: "SPRINGFIELD" })



// 2.3 - Retrieve the number of cities in state "GA" with less than equal 1500 population.
db.zips.find({ state: "GA", pop: { $lte: 1500 } })
// If you want number of cities:
db.zips.aggregate([
  {
    $match: {
      state: "GA",
      pop: { $lte: 1500 }  // Cities with population less than or equal to 1500
    }
  },
  {
    $group: {
      _id: "$city"  // Group by city
    }
  },
  {
    $count: "numberOfCities"  // Count the number of grouped cities
  }
])



// 2.4 - Update all cities from Massachusetts (state: "MA"), a new field { area : "27 340 km"}.
db.zips.updateMany(
  { state: "MA" },
  { $set: { area: "27 340 km" } }
);



// 2.5 - Recover all cities that are located between -81.000001 and 32.915592.
db.zips.find({
  $and: [
    { "loc.0": { $gt: -81.000001 } },  // Longitude (first element in the array)
    { "loc.1": { $lt: 32.915592 } }    // Latitude (second element in the array)
  ]
})



// 2.6 - Update the populations to 50000 for those cities that have a population between 45000 and 50000.
db.zips.updateMany(
  {
    $and: [
      { pop: { $lt: 50000 } },
      { pop: { $gt: 45000 } }
    ]
  },
  {
    $set: { pop: 50000 }
  }
)



// 2.7 - Encontrar la población total de todos los códigos postales:
db.zips.aggregate([
  {
    $group: {
      _id: null,
      totalPopulation: { $sum: "$pop" }
    }
  }
])

// 2.8 - Encontrar la población promedio por ciudad
db.zips.aggregate([
  {
    $group: {
      _id: "$city",
      averagePopulation: { $avg: "$pop" }
    }
  }
])

// 2.9 - Encontrar la ciudad con la menor población
db.zips.aggregate([
  {
    $group: {
      _id: "$city",
      totalPopulation: { $sum: "$pop" }  // Sum population for each city
    }
  },
  {
    $sort: { totalPopulation: 1 }  // Sort by population in ascending order (smallest first)
  },
  {
    $limit: 1  // Limit to the first document, which will be the city with the smallest population
  }
])


// 2.10 - Encontrar la población total y promedio por estado, y ordenar los resultados por población total descendente
db.zips.aggregate([
  {
    $group: {
      _id: "$state",  // Group by state
      totalPopulation: { $sum: "$pop" },  // Calculate total population per state
      avgPopulation: { $avg: "$pop" }  // Calculate average population per state
    }
  },
  {
    $sort: { totalPopulation: -1 }  // Sort by total population in descending order
  }
])


// 2.11 - Encontrar las 5 ciudades con la mayor población en el estado de MA
db.zips.aggregate([
  { $match: { state: "MA" } },  // Match cities in the state "MA"
  {
    $group: {
      _id: "$city",  // Group by city
      population: { $sum: "$pop" }  // Sum population for each city
    }
  },
  { $sort: { population: -1 } },  // Sort by population in ascending order
  { $limit: 5 }  // Limit to the top 5 cities
])


// 2.12 Encontrar la diferencia de población entre la ciudad más poblada y la menos poblada en el estado de MA
db.zips.aggregate([
  {
    $match: { state: "MA" }  // Step 1: Filter for cities in the state "MA"
  },
  {
    $group: {
      _id: "$city",
      population: { $sum: "$pop" }  // Step 2: Group by city and calculate total population for each city
    }
  },
  {
    $group: {
      _id: null,  // Step 3: Group all cities together
      maxPopulation: { $max: "$population" },  // Find the maximum population
      minPopulation: { $min: "$population" }   // Find the minimum population
    }
  },
  {
    $project: {
      _id: 0,  // Exclude _id
      populationDifference: { $subtract: ["$maxPopulation", "$minPopulation"] }  // Step 4: Subtract min from max population
    }
  }
])


// 2.13  Calcula y almacena la población total por estado utilizando el enfoque MapReduce para procesar los datos
var mapFunction = function () {
  emit(this.state, this.pop);  // Emit the state as the key and the population as the value
};

var reduceFunction = function (state, populations) {
  return Array.sum(populations);  // Sum all the populations for a given state
};

db.zips.mapReduce(
  mapFunction,    // The map function
  reduceFunction, // The reduce function
  {
    out: "state_populations"  // Output collection where the result will be stored
  }
);


// 2.14. Calcula y almacena la cantidad de códigos postales por estado utilizando el enfoque MapReduce para procesar los datos.
var mapFunction = function () {
  emit(this.state, 1);  // Emit the state as the key and 1 as the value for each zip code
};

var reduceFunction = function (state, counts) {
  return Array.sum(counts);  // Sum the values (which are all 1) to count the number of zip codes per state
};

db.zips.mapReduce(
  mapFunction,    // The map function
  reduceFunction, // The reduce function
  {
    out: "state_zip_counts"  // Output collection where the result will be stored
  }
);



/* ---------------------------------------------------------- */


// !!!! use Taller !!!! RUN THIS COMMAND FIRST

db.empleados.insertOne({
  nombre: "Juan",
  apellidos: "Torres",
  NSS: 12345,
  DNI: "000000Z",
  fechaNacimiento: ISODate("1960-01-01T00:00:00Z"),
  categoria: "encargado"
})

db.empleados.insertOne({
  "nombre": "Felipe",
  "apellidos": "Fernández",
  "NSS": 1234567891011,
  "DNI": "12345678Z",
  "fechaNacimiento": ISODate("1965-03-15T00:00:00Z"),
  "categoria": "recepcionista",
  "atiende": [
    {
      "DNICliente": "98765432P",
      "vehiculo": {
        "matricula": "2819CTH",
        "numBastidor": "SFZRE11BX73V00011",
        "marca": "Renault",
        "modelo": "Laguna"
      },
      "fechaConsulta": ISODate("2020-03-10T12:24:00Z"),
      "presupuesto": {
        "descripción": "Pintado total",
        "aceptado": false
      }
    },
    {
      "DNICliente": "98827432P",
      "vehiculo": {
        "matricula": "4801CZP",
        "numBastidor": "SFZRE11BX73V00011",
        "marca": "Peugeot",
        "modelo": "607"
      },
      "fechaConsulta": ISODate("2020-03-11T17:54:00Z"),
      "presupuesto": {
        "descripción": "Cambio de ruedas delanteras",
        "piezas": [
          "ruedas michelin all climate",
          "tornillos ruedas delanteras",
          "embellecedores"
        ],
        "aceptado": true
      }
    }
  ]
}
)


db.empleados.insertMany([
  {
    "nombre": "Carmen",
    "apellidos": "Granados",
    "NSS": 35489612549,
    "DNI": "45612378T",
    "fechaNacimiento": ISODate("1973-06-19T00:00:00Z"),
    "categoria": "gerente"
  },
  {
    "nombre": "Susana",
    "apellidos": "Martínez",
    "NSS": 98765432131,
    "DNI": "98765432M",
    "fechaNacimiento": ISODate("1982-10-07T00:00:00Z"),
    "categoria": "currito",
    "trabaja": [
      {
        "idReparacion": 2849165,
        "letrasReparacion": "RTW",
        "semana": 4,
        "nHoras": 8
      },
      {
        "idReparacion": 4698531,
        "letrasReparacion": "HDI",
        "semana": 6,
        "nHoras": 23
      }
    ]
  },
  {
    "nombre": "Federico",
    "apellidos": "Martínez",
    "NSS": 98666662131,
    "DNI": "431215432M",
    "fechaNacimiento": ISODate("1990-10-07T00:00:00Z"),
    "categoria": "currito",
    "trabaja": [
      {
        "idReparacion": 4698531,
        "letrasReparacion": "HDI",
        "semana": 6,
        "nHoras": 23
      }
    ]
  }
]
)


// 3.6 Presentar el nombre y apellidos de todos los empleados ordenados por su fecha de nacimiento
db.empleados.find({}, { nombre: 1, apellidos: 1, fechaNacimiento: 1, _id: 0 }).sort({ fechaNacimiento: 1 })


// 3.7 Localizar todas las personas cuyo apellido empiece por G, o que tengan categoría de gerente o currito
// Last name starts with G
// Category is gerente or currito
db.empleados.find(
  {
    $or: [
      {categoria: "gerente"},
      {categoria: "currito"},
      {$where: "this.apellidos[0] === 'G'"}
    ]
  },
  {nombre: 1, apellidos: 1, _id: 0}
)



// 3.8
db.empleados.insertOne({
  nombre: "Juan",
  apellidos: "Tuercas",
  NSS: 111111,
  DNI: "00000X",
  fechaNacimiento: ISODate("1990-10-07T00:00:00Z"),
  categoria: "currito",
  trabaja: [
    {
      idReparacion: 3663663,
      letrasReparacion: "FFF",
      semana: 6,
      nHoras: 10
    }
  ]
})


// 3.9 - Obtener quienes han trabajado en la orden de reparación 4698531 o en la orden de trabajo 2849165
// 4698531 o 2849165
db.empleados.find(
  {
    "trabaja.idReparacion": { $in: [4698531, 2849165]}
  }
)

// 3.10 - Actualizar el DNI del gerente con otro valor
db.empleados.updateMany(
  { "categoria": "gerente" }, // Use quotes for the field name
  { $set: { "DNI": "123456789M" } } // Quotes around both the field name and value
)


// 3.11 - La inspección de trabajo nos obliga o no poder utilizar 
// la categoría “currito” y la tenemos que cambiar por “mecánico”. 
// Haz el cambio en la base de datos para que no nos multen
db.empleados.updateMany(
  { "category": "currito" },
  { $set: { "category": "mecánico" } }
)

// 3.12 - Localiza los registros de todas las veces que el vehículo de chasis
// SFZRE11BX73V00011 ha sido atendido por el taller
// ¿Qué anomalía se presenta? Utiliza algún criterio para corregirla
db.empleados.find(
  { "atiende.vehiculo.numBastidor": "SFZRE11BX73V00011" }
)

// Two vehicles have the same chasis number which is supposed to be unique.

// We can either delete the incorrect one if we know which one it is.
// It could be an invalid entry or a duplicate of some sort.
db.empleados.updateOne(
  { "atiende.vehiculo.matricula": "2819CTH" },  // Find the vehicle by license plate
  { $pull: { atiende: { "vehiculo.numBastidor": "SFZRE11BX73V00011" } } }  // Remove the incorrect entry
)

// Or we can update the chasis number to a valid one
// if we know the correct number.
db.empleados.updateOne(
  { "atiende.vehiculo.matricula": "2819CTH" },  // Find the correct car by license plate
  { $set: { "vehiculo.numBastidor": "NEW_CORRECT_NUM_BASTIDOR" } }  // Set the correct chassis number
)

// 3.13 - 3.13. Crea un índice textual sobre la descripción de los
// presupuestos y localiza todos los vehículos que se han pintado

db.empleados.createIndex(
  { "atiende.presupuesto.descripción": "text" }
)

db.empleados.find(
  { $text: { $search: "pintado" } },  
  { "atiende.vehiculo": 1, _id: 0 }
)

// 3.14 - Contar el número de empleados que han 
// trabajado en las reparaciones con idReparacion de 2849165 y 4698531
db.empleados.aggregate([
  {
    $match: { "trabaja.idReparacion": { $in: [4698531, 2849165] } }
  },
  {
    $group: {
      _id: "$nombre",  // Group by employee name to get distinct employees
    }
  },
  {
    $count: "totalEmployees"  // Count the number of distinct employees
  }
])


// 3.15 - Listar los nombres distintos de todos los empleados que 
// han trabajado en la reparación con idReparacion de 4698531.
db.empleados.aggregate([
  {
    $match: { "trabaja.idReparacion": 4698531  }
  },
  {
    $group: {
      _id: "$nombre",  // Group by employee name to get distinct employees
    }
  }
])



// 3.16 - Calcular el total de horas trabajadas por cada empleado en todas 
// las reparaciones en las que ha trabajado.
db.empleados.aggregate([
  {
    $unwind: "$trabaja" // Unwind the trabaja array to flatten it
  },
  {
    $group: {
      _id: "$nombre", // Group by employee name
      totalHours: { $sum: "$trabaja.nHoras" } // Sum the nHoras within the trabaja array
    }
  }
])


// 3.17 - 3.17. Encontrar el nombre del empleado que ha 
// trabajado el mayor número de horas en total
db.empleados.aggregate([
  {
    $unwind: "$trabaja" // Unwind the trabaja array to flatten it
  },
  {
    $group: {
      _id: "$nombre", // Group by employee name
      totalHours: { $sum: "$trabaja.nHoras" } // Sum the nHoras within the trabaja array
    }
  },
  {
    $sort: { totalHours: -1 } 
  },
  {
    $limit: 1
  }
])