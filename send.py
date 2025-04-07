import asyncio
from bleak import BleakClient
import struct
import random

xiao_address = "26:37:79:5a:8b:e9"
xiao_address_mac = "E6A89626-3D00-580B-1D80-F613D65739F1"
xiao_service = "19B10000-E8F2-537E-4F6C-D104768A1214"
xiao_read_characteristic = "19B10001-E8F2-537E-4F6C-D104768A1214"
xiao_write_characteristic = "20B1D001-E8F2-537E-4F6C-A104768A1517"

async def printVals(characteristic, data): #callback function must have these parameters
    val1, val2 = struct.unpack('<hh', data)
    print("Received: ", val1, val2)

async def sendVals(freq, client, characteristic):
    sleep_duration = 1/freq
    
    for _ in range(freq): 
        val1 = random.randint(-255, 255)  # Any integer from 0–255
        val2 = random.randint(-255, 255)

        send_bytes = struct.pack('<hh', val1, val2)

        await client.write_gatt_char(characteristic, send_bytes)
        print("Sent: ", val1, val2)
        await asyncio.sleep(sleep_duration)
    
async def main():
    print("Trying to connect...")
    
    async with BleakClient(xiao_address_mac) as client:
        print("Connected.")

        await client.start_notify(xiao_read_characteristic, printVals)
    
         #send 5/10 times within a second. sending 2 pwm values (0-250)
        await sendVals(5, client, xiao_write_characteristic)
            
        await asyncio.sleep(1) #only sends/receives for a second
        await client.stop_notify(xiao_read_characteristic)


asyncio.run(main())