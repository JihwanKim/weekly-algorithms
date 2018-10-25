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

def get_game_type():
    return ["solo","duo","squad"]

def print_stats(stats, type):
    solo_dict = stats.get(type)
    items = stats.get(type).items()
    if solo_dict.get("losses") != 0 or solo_dict.get("top10s") != 0 or solo_dict.get("wins") != 0   :
        items = solo_dict.items()
        msg = ""
        for (key,value) in items :
            msg += "\n" + str(key) + ":" + str(value)
        return "============"+ type + " 전적검색 결과============" + msg


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
        stats = json.loads(response.text).get("data").get("attributes").get("gameModeStats")
        if stats:
            game_types = get_game_type()
            for current_game_type in game_types:
                result = str(print_stats(stats, current_game_type)) 
                if result != "None" : 
                    await client.send_message(message.channel, result)
            

client.run('')

