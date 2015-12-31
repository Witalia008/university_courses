Rails.application.routes.draw do
  match '/pusher/auth' => 'pusher#auth', via: :post

  get 'general/index'
  match 'groups' => 'general#groups', via: [:get], as: 'all_groups'
  match 'users' => 'general#users', via: [:get], as: 'all_users'
  match 'chat' => 'general#chat', via: [:get], as: 'chat'

  devise_for :users
  mount RailsAdmin::Engine => '/admin', as: 'rails_admin'

  scope '/:user_id/' do
    match 'profile' => 'general#profile', via: [:get], as: 'profile'

    resources :messages
    resources :groups do
      match 'join' => 'groups#join', via: [:post], as: 'join'
      match 'leave' => 'groups#leave', via: [:delete], as: 'leave'
      resources :banners
    end
    resources :friends

    match 'befriend' => 'friends#add', via: [:post], as: 'befriend'
    match 'del_friend' => 'friends#remove', via: [:delete], as: 'remove_friend'
  end

  root 'general#index'

  # The priority is based upon order of creation: first created -> highest priority.
  # See how all your routes lay out with "rake routes".

  # You can have the root of your site routed with "root"
  # root 'welcome#index'

  # Example of regular route:
  #   get 'products/:id' => 'catalog#view'

  # Example of named route that can be invoked with purchase_url(id: product.id)
  #   get 'products/:id/purchase' => 'catalog#purchase', as: :purchase

  # Example resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Example resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Example resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Example resource route with more complex sub-resources:
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', on: :collection
  #     end
  #   end

  # Example resource route with concerns:
  #   concern :toggleable do
  #     post 'toggle'
  #   end
  #   resources :posts, concerns: :toggleable
  #   resources :photos, concerns: :toggleable

  # Example resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end
end
