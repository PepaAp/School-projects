const continent = document.getElementById('continent');
const modal = new bootstrap.Modal(document.getElementById('windowCountry'));
const modalBody = document.getElementById('modal-body-content')
const modalHeader = document.getElementById('modal-header-content') 
let map;

async function initMap(lat, lng, area) {
  const { Map } = await google.maps.importLibrary("maps");

  let zoom = 5;
  if (area < 10000) { 
    zoom = 8;
  } else if (area < 100000) { 
    zoom = 6;
  } else if (area < 1000000) { 
    zoom = 4;
  } else if (area > 5000000) { 
    zoom = 3;
  }

  map = new Map(document.getElementById("map"), {
    center: { lat: lat, lng: lng },
    zoom: zoom,
  });
}

async function getData(region) {
    const url = `https://restcountries.com/v3.1/region/${region}`;
    try {
      const response = await fetch(url);
      if (!response.ok) {
        throw new Error(`Response status: ${response.status}`);
      }
  
      const json = await response.json();
      console.log(json);
      let blocks = '';
      json.forEach((country) => {
        blocks += `
            <div class="col-xl-2 col-lg-3 col-md-4 col-sm-6">                
                <div class="card">
                    <img class="card-img-top" src="${country.flags.png}" alt="Vlajka">
                    <div class="card-body">
                      <h4 class="card-title">${country.translations.ces.common}</h4>
                      <p class="card-text">Hl. město: ${country.capital == undefined?"Nemá hl. město":country.capital[0]}</p>
                      <a class="btn btn-info card-link text-white rounded-3" data-name="${country.name.common}">Informace</a>
                    </div>
                </div>
            </div>            
        `;
      });
      listCountries.innerHTML = blocks;
      document.querySelectorAll('[data-name]').forEach(button => {
        button.addEventListener('click', () => {
          const countryName = button.getAttribute('data-name');
          modal.show();
          fetch(`https://restcountries.com/v3.1/name/${countryName}`)
          .then(res => res.json())
          .then(data => {
            const country = data[0];
            modalHeader.innerHTML = `
              <h4>${country.translations.ces.common} ${country.flag}</h4>
            `;
            modalBody.innerHTML = `
              <p>Plný název: ${country.translations.ces.official}</p>
              <p>Hlavní město: ${country.capital[0]}</p>
              <p>Rozloha: ${country.area} km²</p>
              <p>Populace: ${country.population} obyvatel</p>
              <p>Jazyky: ${Object.values(country.languages).join(', ')}</p>
              <p>
                Měna: ${Object.values(country.currencies).map(curr => `${curr.name} (${curr.symbol})`)}
              </p>
              <div id="map"></div>
            `;
            initMap(country.latlng[0], country.latlng[1], country.area);
          })
          .catch(error => {
            console.log(`error with information button. ${error}`);
          })
        });
      });
    } catch (error) {
      console.error(error.message);
    }
  }


continent.addEventListener('change', ()=> {
    getData(continent.value);
});

getData('europe');
