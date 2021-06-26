#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time
import json, requests
from datetime import datetime

def getWeather(city):
    """Return an array of current weather parameters"""
    key = '0a46eee55b59490fb8047e3bdd1032cc'
    cityName = city
    try:
        url = requests.get('https://api.weatherbit.io/v2.0/current?city='+cityName+'&key='+key)
        weatherJSON = json.loads(url.text)
    except requests.status_codes == 204 or ValueError:
        print(cityName, ' is a wrong cityName')  
        return None
    except requests.exceptions.ConnectionError as e:
        print(e)
        return None
    except requests.RequestException as e:
        print(e)
        return None
    data = weatherJSON['data'][0]
    return [data['temp'], data['wind_spd']*(3.6), data['clouds'], data['precip'],data['sunrise'],data['sunset'],data['datetime'],data['aqi'],data['weather']]

def getForecast(city):
    """Return an array of forecast weather parameters"""
    key = 'aCPPJqpqXGtwxyZDs4ajpb1NqH359V34'
    try:
        urlCity = requests.get('http://dataservice.accuweather.com/locations/v1/cities/search?apikey='+key+'&q='+city+'&language=fr-fr&details=true')
        cityJSON = json.loads(urlCity.text)
    except requests.status_codes == 204 or ValueError:
        print(city, ' is a wrong cityName')  
        return None
    except requests.exceptions.ConnectionError as e:
        print(e)
        return None
    except requests.RequestException as e:
        print(e)
        return None
    try:
        urlForecast = requests.get('http://dataservice.accuweather.com/forecasts/v1/daily/1day/'+cityJSON[0]['Key']+'?apikey='+key+'&language=fr-fr&details=true&metric=true')
        forecastJSON = json.loads(urlForecast.text)
    except requests.status_codes == 204 or ValueError:
        print(city, ' is a wrong cityName')  
        return None
    except requests.exceptions.ConnectionError as e:
        print(e)
        return None
    except requests.RequestException as e:
        print(e)
        return None
    dailyForecasts = forecastJSON['DailyForecasts'][0]
    sunRise = dailyForecasts['Sun']['Rise']
    sunSet = dailyForecasts['Sun']['Set']
    tempMin = dailyForecasts['Temperature']['Minimum']['Value']
    tempMax = dailyForecasts['Temperature']['Maximum']['Value']
    airQuality = dailyForecasts['AirAndPollen'][0]['Value']
    hoursOfSun = dailyForecasts['HoursOfSun']
    windSpeed = dailyForecasts['Day']['Wind']['Speed']['Value']
    rain = dailyForecasts['Day']['Rain']['Value']
    snow = dailyForecasts['Day']['Snow']['Value']
    cloud = dailyForecasts['Day']['CloudCover']
    shortPhrase = dailyForecasts['Day']['ShortPhrase']
    hasPrecipitation = dailyForecasts['Day']['HasPrecipitation']
    return [sunRise, sunSet, tempMin, tempMax, airQuality, hoursOfSun, windSpeed, rain, snow, cloud, shortPhrase, hasPrecipitation]

def sendData(data, ok):
    """Send data to the arduino card with ok string"""
    arduino.write(data.encode())
    while arduino.inWaiting()==0: pass
    if  arduino.inWaiting()>0: 
        while (arduino.readline().decode('utf-8')!=ok) : time.sleep(0.1)
    arduino.flushInput()
    time.sleep(1)

def readData():
    """Read arduino card answer"""
    while arduino.inWaiting()==0: pass
    if  arduino.inWaiting()>0:
        ans = arduino.readline().decode('utf-8')
        return ans
    return None

if __name__ == '__main__':

    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyUSB0", 9600, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))      
            try:
                while True:
                    city=""
                    
                    test = readData()
                    if(test!=None):
                        answer = test #Mode

                    # Forecast #
                    if (answer =="ppp") :
                        test = readData()
                        if(test!=None):
                            answer2 = test #City

                        #Forecast Data
                        prev = getForecast(answer2)
                        if(prev == None):
                            continue
                        tempMin = "www" + str(prev[2])
                        tempMax = "vvv" + str(prev[3])
                        airQuality = "nnn" + str(prev[4])
                        hoursOfSun = "mmm" + str(prev[5])
                        windSpeed = "lll" + str(prev[6])
                        rain = "kkk" + str(prev[7])
                        snow = "jjj" + str(prev[8])
                        cloud = "sss" + str(prev[9])
                        phrase = "rrr" + str(prev[10])
                        precipitation = "ttt" + str(prev[11])

                        forecastData = {"ok2": tempMin, "ok3": tempMax, "ok4": airQuality, "ok5": hoursOfSun, "ok6": windSpeed, "ok7": rain, "ok8": snow, "ok9": cloud,
                        "ok10": phrase, "ok11": precipitation}

                        arduino.flushInput()
                        time.sleep(1)

                        # Sending data to the arduino
                        for ok, data in forecastData.items():
                            sendData(data, ok)

                        print("FINISH100")            
                    
                    # Current Weather #
                    if (answer =="aaa") :
                        test = readData()
                        if(test!=None):
                            answer2 = test #City
                            

                        city = answer2
                        print(city, "<=====")

                        # Current Weather Data
                        tab = getWeather(city)
                        if(tab == None):
                            continue
                        temp = "ddd" + str(tab[0])
                        vent = "ccc" + str(tab[1])
                        nuage = "fff" + str(tab[2])
                        pluie = "bbb" + str(tab[3])
                        rise = tab[4]
                        sett = tab[5]
                        # Compute sun rise/sett 
                        dateNow = datetime.utcnow()
                        dateSunRise = datetime.strptime(rise,'%H:%M')
                        dateSunSet = datetime.strptime(sett,'%H:%M')
                        sun = dateSunRise.time() < dateNow.time() < dateSunSet.time()
                        if(sun):
                            soleil ="eee1"
                        else:
                            soleil ="eee0"
                        
                        time.sleep(1)
                        arduino.flushInput()
                    
                        currentWeatherData = {"ok1": temp, "ok2": vent, "ok3": pluie, "ok4": nuage, "ok5": soleil}
                        for ok, data in currentWeatherData.items():
                            sendData(data, ok)
                    
                        print(tab)
                        arduino.flushInput() #remove data after reading
                     
                    rep ="ok1"
                    arduino.write(rep.encode())
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")
