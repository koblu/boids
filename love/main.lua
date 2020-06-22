local json = require "lib/json"

local framerate = 60
local arena_width, arena_height = 100, 100
local dt_needed = 1/framerate
local time_acc = 0;
local io_channel, io_thread
local bird_pos = {}

function love.load()
    io_channel = love.thread.getChannel("io")
    io_thread = love.thread.newThread("io.lua")
    io_thread:start()
end

function love.draw()
    local mess
    if (time_acc >= dt_needed) then
        time_acc = 0;

        io_channel = love.thread.getChannel("io")
        mess = io_channel:pop()
        local status, mess_json = pcall(json.decode, mess)
        if status then
            bird_pos = mess_json
        end
    end
    for _, v in ipairs(bird_pos) do 
        love.graphics.circle("fill", (v[1]/arena_width) * love.graphics.getWidth(), (v[2]/arena_height) * love.graphics.getHeight(), 2);
    end
end

function love.update(dt)
    time_acc = time_acc + dt
end
