const continent = document.getElementById('continent');

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
        blocks += `<div class="col-xl-2 col-lg-3 col-md-4 col-sm-6">
                    <div class="card">
                        <img src="${country.flags.png}" alt="" class="card-img-top">
                        <div class="card-body">
                            <h4 class="card-title">${country.traslate.ces.common}</h4>
                            <p class="card-text">${country.capital[0]}</p>
                            <a href="" class="btn btn-info card-link"></a>
                            <!-- dalsi info -->
                        </div>
                    </div>
                </div>`
                ;
      });
      listCountries.innerHTML = blocks;
    } catch (error) {
      console.error(error.message);
    }
  }

continent.addEventListener('change', () => {
    getData(continent.value);
})

getData('europe');