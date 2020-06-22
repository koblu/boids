function io_thread()
    local input = love.thread.getChannel("io");

    while true do
        local mess = io.read()
        --print(mess)
        input:push(mess)
    end
end
io_thread()