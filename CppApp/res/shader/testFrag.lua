verying = {}
uniform = {
}

local ambientStrength = 0.1
local lightColor = {1, 1, 1}
local lightPos = {1, 1, 1}
local viewPos = {0, 0, 3}
local specularStrength = 0.5
function main()
    local objColor = cr.texture2D(uv, texture)
    objColor[4] = nil

    local norm = cr.normalize(normal)
    local lightDir = cr.normalize(cr.sub(lightPos, pos))

    local ambient = cr.mul(ambientStrength, lightColor)

    local diff = math.max( cr.dot(norm, lightDir), 0.0)
    local diffuse = cr.mul(diff, lightColor)

    local viewDir = cr.normalize(cr.sub(viewPos, pos))
    local reflectDir = cr.reflect(cr.sub({0.0,0.0,0.0}, lightDir), norm)
    local spec = math.max(cr.dot(viewDir, reflectDir)*1, 0.0)^32
    -- print(spec)
    local specular = cr.mul(spec * specularStrength, lightColor)

    local result = cr.mul(cr.add(cr.add(ambient, diffuse), specular), objColor)
    -- local result = cr.mul(diffuse, objColor)
    -- local result = diffuse
    cr_Color = result
    cr_Color[4] = 1;
end

