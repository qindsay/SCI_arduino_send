import asyncio
from bleak import BleakClient
import struct

xiao_address = "26:37:79:5a:8b:e9"
xiao_address_mac = "E6A89626-3D00-580B-1D80-F613D65739F1"
xiao_service = "19B10000-E8F2-537E-4F6C-D104768A1214"
xiao_characteristic = "19B10001-E8F2-537E-4F6C-D104768A1214"

async def printVal(characteristic, data):
    print(struct.unpack('<f', data)[0])

async def main():
    print("Trying to connect...")
    
    async with BleakClient(xiao_address_mac) as client:
        print("Connected.")

        await client.start_notify(xiao_characteristic, printVal)
        await asyncio.sleep(1)
        await client.stop_notify(xiao_characteristic)


asyncio.run(main())