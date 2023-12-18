import System.IO

type Contato = (String, Int, String, String) -- todo contato é uma tupla com 4 componentes

retorna_nome :: Contato -> String
retorna_nome (nome, tel, ender, relac) = nome

nomes_iguais :: Contato -> Contato -> Bool
nomes_iguais (nome1, telefone1, endereco1, relacao1) (nome2, telefone2, endereco2, relacao2) =
  nome1 == nome2

buscar_dados :: [Contato] -> String -> Contato
buscar_dados [] _ = ("", 0, "", "")
buscar_dados ((nome, tel, ender, relac) : restante_contatos) str
    | str == nome = (nome, tel, ender, relac)
    | otherwise = buscar_dados restante_contatos str


remover_contato :: [Contato] -> Contato -> [Contato]
remover_contato [] _ = []
remover_contato (contato : restante_contatos) contato_procurado
    | contato == contato_procurado = remover_contato restante_contatos contato_procurado
    | otherwise = contato : remover_contato restante_contatos contato_procurado


existe_contato :: [Contato] -> String -> Bool
existe_contato [] str = False
existe_contato _ "" = False
existe_contato ((nome, tel, ender, relac) : restante_contatos) str
    | nome == str = True
    | otherwise = existe_contato restante_contatos str


editar_contato :: [Contato] -> Contato -> [Contato]
editar_contato [] _ = []
editar_contato contatos contato_atualizado =
    map (\c -> if (nomes_iguais c contato_atualizado) then contato_atualizado else c) contatos
    
    
inserir_contato :: [Contato] -> Contato -> [Contato]
inserir_contato contatos contato
    | existe_contato contatos (retorna_nome contato) = editar_contato contatos contato
    | otherwise = contato : contatos


exibir_contatos :: [Contato] -> IO ()
exibir_contatos [] = putStrLn "Nenhum contato cadastrado!"
exibir_contatos contatos = mapM_ exibir_contato contatos


exibir_contato :: Contato -> IO ()
exibir_contato (nome, tel, ender, relac) =
    putStrLn $ "Nome: " ++ nome ++ "\nTelefone: " ++ show tel ++ "\nEndereço: " ++ ender ++ "\nRelação: " ++ relac ++ "\n"


exibir_contato_procurado :: [Contato] -> String -> IO ()
exibir_contato_procurado contatos nome_procurado
    | existe_contato contatos nome_procurado = exibir_contato contatoEncontrado
    | otherwise = putStrLn "Contato não encontrado!"
  where
    contatoEncontrado = buscar_dados contatos nome_procurado

formatar_contato :: Contato -> String
formatar_contato (nome, tel, ender, relac) =
    nome ++ ";" ++ show tel ++ ";" ++ ender ++ ";" ++ relac
    
agenda :: [Contato]
agenda = [("Fulano", 99999999, "Rua A", "UFF"), ("Ciclano", 88888888, "Rua B", "Cederj"), ("Beltrano", 88889999, "Rua C", "Infancia")]
    

escrever_contatos :: FilePath -> [Contato] -> IO ()
escrever_contatos arquivo contatos = writeFile arquivo (unlines $ map formatar_contato contatos)
  where
    formatar_contato (nome, idade, telefone, email) =
      nome ++ "," ++ show idade ++ "," ++ telefone ++ "," ++ email


ler_contatos :: FilePath -> IO [Contato]
ler_contatos arquivo = do
  conteudo <- readFile arquivo
  return $ map parseContato $ lines conteudo
  where
    parseContato linha = case splitOn "," linha of
      [nome, telStr, endereco, instituicao] ->
        (nome, read telStr, endereco, instituicao)
      _ -> error "Formato de contato inválido"
  
      
splitOn :: String -> String -> [String]
splitOn delimiter = unfoldr (split delimiter)
  where
    split :: String -> String -> Maybe (String, String)
    split _ [] = Nothing
    split delim str = Just (break (== head delim) str)


unfoldr :: (b -> Maybe (a, b)) -> b -> [a]
unfoldr f x = case f x of
  Nothing -> []
  Just (y, z) -> y : unfoldr f z


main::IO()
main = do
