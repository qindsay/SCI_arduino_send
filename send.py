import asyncio
from bleak import BleakClient
from bleak import BleakScanner

# from bleak import BleakGATTCharacteristic

xiao_address = "26:37:79:5a:8b:e9"
xiao_address_mac = "E6A89626-3D00-580B-1D80-F613D65739F1"
xiao_service = "19B10000-E8F2-537E-4F6C-D104768A1214"
xiao_characteristic = "19B10001-E8F2-537E-4F6C-D104768A1214"

async def printVal(characteristic, data):
    print("received")

async def main():
    print("trying to connect...")
    # devices = await BleakScanner.discover()
    # device = None
    # for d in devices:
    #     print(d.name)
    #     if d.name == "MyTest":
    #         device = d
    #         print(f"found {device.name}")
    #         break
    #     #print(f"{d.name} - {d.address}")
    # if device is None:
    #     print("Device not found.")
    #     return
    
    async with BleakClient(xiao_address_mac) as client:
        print("connected")
        
        services = await client.get_services()
        if any(service.uuid == xiao_service for service in services):
            print(f"Service {xiao_service} found on the device.")
        else:
            print(f"Service {xiao_service} not found on the device.")
            return
        # print("beginning notification")

        # await client.start_notify(xiao_characteristic, printVal)
        # await client.stop_notify(xiao_characteristic)


asyncio.run(main())