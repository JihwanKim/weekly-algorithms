import discord
import asyncio
import requests
import json

client = discord.Client()

pubg_key = ""
def pubg_call(URI):
    headers = {"Authorization": "Bearer " + pubg_key, "Accept": "application/vnd.api+json"}
    response = requests.get(URI, headers = headers) 
    return response


@client.event
async def on_ready():
    print('Logged in as')
    print(client.user.name)
    print(client.user.id)
    print('------')

@client.event
async def on_message(message):
    if message.content.startswith('!test'):
        counter = 0
        tmp = await client.send_message(message.channel, 'Calculating messages...')
        async for log in client.logs_from(message.channel, limit=100):
            if log.author == message.author:
                counter += 1

        await client.edit_message(tmp, 'You have {} messages.'.format(counter))
    elif message.content.startswith('!sleep'):
        await asyncio.sleep(5)
        await client.send_message(message.channel, 'Done sleeping')

    elif message.content.startswith('!전적검색 '):
        user_id = message.content[6:]
        response = pubg_call('https://api.pubg.com/shards/pc-krjp/players?filter[playerNames]=' + user_id )
        id = json.loads(response.text).get("data")[0].get("id")

        response = pubg_call('https://api.pubg.com/shards/steam/players/'+id+'/seasons/division.bro.official.pc-2018-01' )
        Stats = json.loads(response.text).get("data").get("attributes").get("gameModeStats")
        squad_dict = Stats.get("squad")
        if squad_dict.get("losses") != 0 or squad_dict.get("top10s") != 0 or squad_dict.get("wins") != 0   :
            items = squad_dict.items()
            msg = ""
            for (key,value) in items :
                msg += "\n" + str(key) + ":" + str(value)
            await client.send_message(message.channel, "============Squad 전적검색 결과============" + msg)
        duo_dict = Stats.get("duo")
        if duo_dict.get("losses") != 0 or duo_dict.get("top10s") != 0 or duo_dict.get("wins") != 0   :
            items = duo_dict.items()
            msg = ""
            for (key,value) in items :
                msg += "\n" + str(key) + ":" + str(value)
            await client.send_message(message.channel, "============Duo 전적검색 결과============" + msg)

        solo_dict = Stats.get("duo")
        items = Stats.get("solo").items()
        if solo_dict.get("losses") != 0 or solo_dict.get("top10s") != 0 or solo_dict.get("wins") != 0   :
            items = solo_dict.items()
            msg = ""
            for (key,value) in items :
                msg += "\n" + str(key) + ":" + str(value)
            await client.send_message(message.channel, "============Solo 전적검색 결과============" + msg)

client.run('')

